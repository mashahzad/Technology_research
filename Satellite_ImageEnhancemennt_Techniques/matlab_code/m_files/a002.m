% Case Study: Rural Satellite Image Processing with Sobel Filter and High-Pass Filters

% Read the input image (Assuming it's in grayscale for simplicity)
input_image = imread('rural_satellite_image.jpg');

% Check if the image is in RGB, convert to grayscale if needed
if size(input_image, 3) == 3
    input_image = rgb2gray(input_image);
end

% Display the input image
figure;
subplot(1, 2, 1);
imshow(input_image);
title('Input Image (Agricultural Fields)');

% Apply Sobel filter to detect edges
sobel_filter = fspecial('sobel'); % Sobel filter kernel
sobel_edges = imfilter(double(input_image), sobel_filter, 'replicate');

% Apply high-pass filtering by subtracting low-frequency components
% First, apply a Gaussian low-pass filter to get the low-frequency version of the image
hsize = 5;  % Filter size for Gaussian
sigma = 2.0;  % Standard deviation for Gaussian filter
gaussian_filter = fspecial('gaussian', hsize, sigma);

% Apply Gaussian filter (low-pass filter)
low_freq_image = imfilter(double(input_image), gaussian_filter, 'replicate');

% High-pass filter: subtract low-frequency image from original to get high-pass components
high_pass_image = double(input_image) - low_freq_image;

% Display the Sobel edge-detected image and high-pass filtered image
subplot(1, 2, 2);
imshow(high_pass_image, []);
title('Output Image (High-Pass Filtered for Distinct Boundaries)');
