# TerminalImg
> Console output images, supporting multiple formats such as png, jpg, gif, bmp, etc. (only on Windows)

## usage
> Support two methods: console direct output and pop-up window display of images, respectively

```cpp
// windowName: window title
// windowX: X-axis offset
// windowY: Y-axis offset
// windowWidth: Window Width
// windowHeight: window Height
// img_path: Image Path
if (PopImg("terminal-img", 0, 0, 500, 500, "1.gif") != 0) {
	printf("Picture pop-up failed!\n");
}

// img_path: Image Path
// offsetX: X-axis offset
// offsetY: Y-axis offset
if (ConsoleImg("1.gif", 0, 0) != 0) {
	printf("Console image output failed!\n");
}
```