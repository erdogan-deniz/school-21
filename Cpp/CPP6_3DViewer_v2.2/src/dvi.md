# 3DViewer 2.1

## Info
A program for viewing 3D models from .obj files

Created with Qt + OpenGL, QtGifImage is taken from [here](https://github.com/dbzhang800/QtGifImage)

## Dependencies
1. Qt6.2.4 + QtOpenGLWidgets + OpenGL
2. g++
3. Make and CMake


## Install
1. Download the repository
2. cd to src folder
3. Type `make install`
4. Go to Desktop and run program **3DViewer 2.1**

## Uninstall
Go to src folder and type `make uninstall` or just delete app icon

## Usage
* To open a *.obj file, go to File -> Open or Press **⌘1** and open the desired file.
* To close a file, go to the tab File -> Close or Press **⌘2** and the object will be deleted.
* To see information about the object, you need to go to the tab File -> Info or Press **I**, after which the information about the current object will be displayed.
* To hide the settings window, go to Settings -> Hide/Show or Press **⌘3**, then the settings window will be closed or opened if it was closed.
* To change the projection type, go to Settings -> (Press **O**)Orthographic/Perspective(Press **P**), then the projection type will be changed.
* To make a screenshot, go to the Create -> Image tab, then select the format of the screenshot and save it.
* To make a gif-animation, you need to go to the tab Create -> GIF, after which the main window shows a red frame, indicating that the recording is in progress. After 5 seconds, the recording will be saved(10fps).
* To set the color of the lines, click the **Set Lines Color** button and select the desired color.
* To change the thickness of the lines, move the **Line Width** slider to the right to increase and to the left to decrease.
* To draw a line with dashed lines, click the **Dashed** button, and to draw a solid line, click the **Solid** button.
* To change the color of the vertices, click the **Set Vertex Color** button and select the desired color.
* To change the size of the vertices, slide the **Vertex Size** slider to the right to increase and to the left to decrease.
* To remove the display of vertices, click the **None** button.
* To draw the vertices as a circle, click the **Circle** button.
* To draw the vertices as a square, click the **Square** button.
* To rotate the figure relative to the X, Y, Z axes, hover over the desired coordinate in the **Rotate** section and change it with the mouse wheel.
* To move the figure relative to the X, Y, Z axes, hover over the desired coordinate in the **Move** section and change it with the mouse wheel.
* To resize the shape, move the **Scale** slider to the right to zoom in, or hover the mouse over the spinbox to zoom out.
* To change the background color, click the **Set Background Color** button, select the desired color, and then the background will change.

### 2.1 UPDATE
* To use light, first load the model with normals(vn), enable it in Settings -> **Light** (on by default), change the projection type to non-wireframe if the **Light** button is dimmed, than your model does not support light.
* You can change the projection of the light: press **Flat Shading** for the average polygon color or **Smooth Shading** to enable interpolation.
* You can always return to wireframe mode by simply pressing the **Wireframe** button.
* You can change the position of the light source in X, Y, Z coordinates, just enter a new position or change it with the mouse wheel.
* You can change the light intensity with R, G, B, just enter a new value(0.1 - 1.0) for each component or change it with the mouse wheel.
* To load a texture on a model, first, it must have texture coordinates (vt), if there are, press the **Apply texture** button and select the **.bmp** image, otherwise your model does not support texture mapping.
* To unload a texture, click **Unload Texture**, it will be removed from memory.
* If you change the display type to wireframe, with loaded texture, the texture will also be removed.
* You can save the UV-Map, the image should be on the texture at this point, click the **Save UV-Map** button and select a save location.

## Created and tested on MacOS by [v3ssel](https://github.com/v3ssel), [madamkyl](https://github.com/Viki2302) and [bailagda](https://github.com/bailagda) in 2023
