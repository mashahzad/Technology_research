% Case Study: Urban Area Image Processing with Gaussian Filter

% Read the input image (Assuming it's in grayscale for simplicity)
input_image = imread('urban_image.jpg');

% Check if the image is in RGB, convert to grayscale if needed
if size(input_image, 3) == 3
    input_image = rgb2gray(input_image);
end

% Display the input image
figure;
subplot(1, 2, 1);
imshow(input_image);
title('Input Image (with High-Frequency Noise)');

% Add high-frequency noise (if needed, simulate the noise)
noisy_image = imnoise(input_image, 'gaussian', 0, 0.02); % Gaussian noise with mean 0 and variance 0.02

% Apply a Gaussian filter to reduce the high-frequency noise
% Define Gaussian filter parameters
hsize = 5;  % Filter size (5x5)
sigma = 1.0;  % Standard deviation for Gaussian filter

% Create the Gaussian filter
gaussian_filter = fspecial('gaussian', hsize, sigma);

% Apply the filter to the noisy image
output_image = imfilter(noisy_image, gaussian_filter, 'symmetric');

% Display the output image after processing
subplot(1, 2, 2);
imshow(output_image);
title('Output Image (After Gaussian Filtering)');

% provide image as "urban_image.jpg"