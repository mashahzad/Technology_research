% Case Study: Urban Satellite Image Enhancement Using Bilateral Filtering + Histogram Equalization

% Read the input urban satellite image (Assuming it's in grayscale for simplicity)
input_image = imread('urban_satellite_image.jpg');  % Replace with your urban satellite image file

% If the image is in RGB, convert to grayscale for simplicity
if size(input_image, 3) == 3
    input_image = rgb2gray(input_image);
end

% Display the input image
figure;
subplot(1, 3, 1);
imshow(input_image);
title('Input Image (Urban Satellite Image)');

% Step 1: Apply Bilateral Filtering
% Bilateral filtering smooths the image while preserving edges.
% The 'im bilateral' function in MATLAB can be used to apply bilateral filtering.

% Parameters for Bilateral Filter: 
% sigma_d (spatial domain standard deviation) controls the extent of smoothing
% sigma_r (range domain standard deviation) controls the amount of smoothing based on pixel intensity differences
sigma_d = 5;  % Spatial standard deviation
sigma_r = 0.1; % Range standard deviation (controls the intensity smoothing)

% Apply the bilateral filter
bilateral_filtered_image = imbilatfilt(input_image, sigma_d, sigma_r);

% Step 2: Perform Histogram Equalization
% After bilateral filtering, apply histogram equalization to enhance contrast.
equalized_image = histeq(bilateral_filtered_image);

% Step 3: Display the enhanced image after bilateral filtering and histogram equalization
subplot(1, 3, 2);
imshow(bilateral_filtered_image);
title('Bilateral Filtering Applied');

subplot(1, 3, 3);
imshow(equalized_image);
title('Enhanced Image (Bilateral + HE)');
