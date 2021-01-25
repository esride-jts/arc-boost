import os
import sys

# Just for integration testing
sys.path.append(os.path.dirname(__file__))

# Import the native Python modules
import arcboost



"""
Creates a two dimensional convex hull using x and y coordinates.
"""
def convex_hull(x_coords, y_coords):
    return arcboost.convex_hull(x_coords, y_coords)



class Tool(object):
    """
    Represents a simple wrapper for a C++ tool.
    """

    def __init__(self, toolbox, tool_index):
        self._toolbox = toolbox
        self._tool_index = tool_index

    @property
    def label(self):
        """
        The label of this tool.
        """
        return self._toolbox.tool_label(self._tool_index)

    @property
    def description(self):
        """
        The description of this tool.
        """
        return self._toolbox.tool_description(self._tool_index)

    def parameter_info(self):
        """
        Returns the parameter infos of this tool.
        """
        return self._toolbox.tool_parameter_info(self._tool_index)

    def execute(self, parameters, messages):
        """
        Executes this tool.
        """
        self._toolbox.tool_execute(self._tool_index, parameters, messages)



class ToolRegistry(object):
    """
    Manages all available custom C++ tools.
    """

    def __init__(self):
        self._tool_labels = []
        self._tools = []
        arcboost_toolbox = arcboost.create_toolbox('C++ Geospatial Tools', 'cpp_geospatial_tools')
        self._tool_labels.extend(arcboost.tools())
        self._tools.extend([Tool(arcboost_toolbox, tool_index) for tool_index in range(0, len(self._tool_labels))])
    
    def find_tool(self, tool_label):
        """
        Returns the tool having the specified label otherwise None is returned.
        """
        for tool_index in range(0, len(self._tool_labels)):
            known_label = self._tool_labels[tool_index]
            if tool_label == known_label:
                return self._tools[tool_index]

        return None

    def list_tools(self):
        """
        Returns all tool names/labels being registered.
        """
        return self._tool_labels
        