% Case Study: Coastal Region Image Enhancement Using Gamma Correction

% Read the input satellite image (Assuming it's in grayscale for simplicity)
input_image = imread('coastal_region_image.jpg');  % Replace with your coastal satellite image file

% If the image is in RGB, convert to grayscale for simplicity
if size(input_image, 3) == 3
    input_image = rgb2gray(input_image);
end

% Display the input image
figure;
subplot(1, 2, 1);
imshow(input_image);
title('Input Image (Coastal Region with Varying Lighting Conditions)');

% Step 1: Apply Gamma Correction
% Gamma correction formula: output = c * input_image ^ gamma
% Where c is a constant (usually 1) and gamma is the correction factor
gamma = 0.8;  % Gamma value less than 1 brightens the dark areas

% Normalize the image to the range [0, 1] before applying gamma correction
normalized_image = double(input_image) / 255;

% Apply the gamma correction
gamma_corrected_image = normalized_image .^ gamma;

% Rescale the image back to the range [0, 255]
gamma_corrected_image = uint8(gamma_corrected_image * 255);

% Step 2: Display the enhanced image after gamma correction
subplot(1, 2, 2);
imshow(gamma_corrected_image);
title('Enhanced Image (After Gamma Correction)');
