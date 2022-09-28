# Mandelbrot Explorer

Made with OpenGL and GLFW.

I will add navigation with mouse/kbd and I will add a feature to load up a texture to color the set.


## What is Mandelbrot Set?
Understanding the Mandelbrot Set is probably the hardest part of doing this.
Mandelbrot set is the set of Complex numbers that remain bounded when f(z) = z^2 + c is applied to them arbitrarily many times.

1. Every pixel on the screen represents the complex numbers.
2. x is real part, y is the complex part for each number.
3. The color of each pixel represents how many times we can apply f(z) function to the complex number represented by that pixel.
4. Since we cannot use infinity, we set up an integer value for accuracy (used 255).
5. Also we decide on what positive float will be the absolute value for the boundedness (used 2).

## How does it look like?

Well it looks like this. White/gray parts are the pixels that remained bounded by a certain value. I used 255 as the number of iterations and the color output is (number of iterations that remained below 2)/255 so it is between 0 and 1.

I also added some lerping effect to the keyboard controls so it does not jitter around and it is pleasant to navigate.

![Screenshot (8)](https://user-images.githubusercontent.com/47000155/189583088-747c887a-2f88-4716-8045-d4ec66fa5829.png)
