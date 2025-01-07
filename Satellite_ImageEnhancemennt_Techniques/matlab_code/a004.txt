% Case Study: Forested Area Image Processing Using Fourier Transform to Remove High-Frequency Noise

% Read the input image (Assuming it's in grayscale for simplicity)
input_image = imread('forest_satellite_image.jpg');

% Check if the image is in RGB, convert to grayscale if needed
if size(input_image, 3) == 3
    input_image = rgb2gray(input_image);
end

% Display the input image with high-frequency noise
figure;
subplot(1, 2, 1);
imshow(input_image);
title('Input Image (Forested Area with Noise)');

% Step 1: Perform Fourier Transform to get the frequency domain representation
fft_image = fft2(double(input_image)); % 2D Fourier Transform of the image

% Step 2: Shift the zero-frequency component to the center of the spectrum
fft_shifted = fftshift(fft_image);

% Step 3: Create a high-pass filter to isolate high-frequency noise
% You can use a simple circular mask in the frequency domain
[M, N] = size(fft_shifted);
center_x = round(M / 2);
center_y = round(N / 2);
radius = 30; % The radius for the high-pass filter (can be adjusted)

% Create a mask that is 1 inside the low-frequency area and 0 outside
mask = ones(M, N);
[x, y] = meshgrid(1:N, 1:M);
distance_from_center = sqrt((x - center_y).^2 + (y - center_x).^2);
mask(distance_from_center < radius) = 0;  % Set low frequencies to 0

% Step 4: Apply the high-pass filter to the frequency domain image
filtered_fft_shifted = fft_shifted .* mask;

% Step 5: Shift back the frequency components to the original position
filtered_fft = ifftshift(filtered_fft_shifted);

% Step 6: Perform the inverse Fourier Transform to get the processed image in the spatial domain
filtered_image = ifft2(filtered_fft);
filtered_image = real(filtered_image); % Take the real part as the output image

% Step 7: Display the filtered image after applying inverse FFT
subplot(1, 2, 2);
imshow(filtered_image, []);
title('Output Image (After Fourier Transform Filtering)');
