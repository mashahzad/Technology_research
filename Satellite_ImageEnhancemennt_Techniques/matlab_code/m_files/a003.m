% Case Study: Coastal Region Image Processing with Median Filter to Remove Salt-and-Pepper Noise

% Read the input image (Assuming it's in grayscale for simplicity)
input_image = imread('coastal_region_image.jpg');

% Check if the image is in RGB, convert to grayscale if needed
if size(input_image, 3) == 3
    input_image = rgb2gray(input_image);
end

% Display the input image
figure;
subplot(1, 2, 1);
imshow(input_image);
title('Input Image (Coastal Region with Salt-and-Pepper Noise)');

% Add salt-and-pepper noise to the image (if not already noisy)
noisy_image = imnoise(input_image, 'salt & pepper', 0.02); % 0.02 is the noise density

% Apply a median filter to remove salt-and-pepper noise
filtered_image = medfilt2(noisy_image, [3 3]); % 3x3 median filter

% Display the filtered image after applying the median filter
subplot(1, 2, 2);
imshow(filtered_image);
title('Output Image (After Median Filter)');
