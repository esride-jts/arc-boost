import arcpy
import geospatial
import os

class Toolbox(object):
    def __init__(self):
        self.label =  'C++ Geospatial Integration toolbox'
        self.alias  = 'arcboost_integration'
        self.tools = [ConvexHullTool]
        


class ConvexHullTool(object):
    """
    Creates the convex hull from point features.
    """
    
    def __init__(self):
        self.label = "Convex Hull"
        self.description = "Creates the convex hull from point features."

    def getParameterInfo(self):
        in_param = arcpy.Parameter(
            displayName="Input Features",
            name="in_features",
            datatype="GPFeatureLayer",
            parameterType="Required",
            direction="Input")
        
        out_param = arcpy.Parameter(
            displayName="Output Features",
            name="out_features",
            datatype="GPFeatureLayer",
            parameterType="Required",
            direction="Output")
        return [in_param, out_param]

    def isLicensed(self): #optional
        return True

    def updateParameters(self, parameters): #optional
        return

    def updateMessages(self, parameters): #optional
        return

    def execute(self, parameters, messages):
        in_features = parameters[0].valueAsText
        in_catalog_path = arcpy.Describe(in_features).catalogPath
        wgs84 = arcpy.SpatialReference(4326)
        x_coords = []
        y_coords = []
        with arcpy.da.SearchCursor(in_catalog_path, ["SHAPE@X", "SHAPE@Y"], spatial_reference=wgs84) as cursor:
            for in_feature in cursor:
                x_coords.append(in_feature[0])
                y_coords.append(in_feature[1])
        
        out_features = parameters[1].valueAsText
        workspace_path = os.path.dirname(out_features)
        table_name = os.path.basename(out_features).rstrip(os.path.splitext(out_features)[1])
        feature_class_result = arcpy.management.CreateFeatureclass(workspace_path, table_name, geometry_type="POLYGON", spatial_reference=wgs84)
        feature_class = feature_class_result[0]
        
        convex_hull = geospatial.convex_hull(x_coords, y_coords)

        with arcpy.da.InsertCursor(feature_class, ["SHAPE@"]) as insert_cursor:
            insert_cursor.insertRow([convex_hull])
