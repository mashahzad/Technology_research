% Case Study: Forest Area Image Enhancement Using Linear Contrast Stretching

% Read the input multispectral image (Assuming it's in grayscale or single-band for simplicity)
input_image = imread('forest_area_image.jpg');  % Replace with your multispectral image file

% If the image is in RGB, convert to grayscale for simplicity
if size(input_image, 3) == 3
    input_image = rgb2gray(input_image);
end

% Display the input image
figure;
subplot(1, 2, 1);
imshow(input_image);
title('Input Image (Forest Area with Similar Tree Canopy and Soil Colors)');

% Step 1: Perform Linear Contrast Stretching
% The formula for linear contrast stretching is:
%   output = (input - min) / (max - min) * (new_max - new_min) + new_min
% Here, we use new_min = 0 and new_max = 255 for 8-bit images.

min_value = double(min(input_image(:)));  % Minimum pixel value in the input image
max_value = double(max(input_image(:)));  % Maximum pixel value in the input image

% Perform the contrast stretching
stretched_image = uint8((double(input_image) - min_value) / (max_value - min_value) * 255);

% Step 2: Display the enhanced image after linear contrast stretching
subplot(1, 2, 2);
imshow(stretched_image);
title('Enhanced Image (After Linear Contrast Stretching)');
