#include "project_tools.h"

void additBrighten(cv::Mat & image, const int beta)
{
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int channel = 0; channel < image.channels(); channel++)
			{
				image.at<Vec3b>(y, x)[channel] = saturate_cast<uchar>(image.at<Vec3b>(y, x)[channel] + beta);
			}
		}
	}
}

int multiBrighten(cv::Mat & image, const float c)
{
	if (c < 0)
	{
		cout << "Multiplicative Brighten not applied: The c parameter must be non negative" << endl;
		return 0;
	}

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int channel = 0; channel < image.channels(); channel++)
			{
				image.at<Vec3b>(y, x)[channel] = saturate_cast<uchar>(image.at<Vec3b>(y, x)[channel] * c);
			}
		}
	}

	return 1;
}

void negative(Mat & image)
{
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int channel = 0; channel < image.channels(); channel++)
			{
				image.at<Vec3b>(y, x)[channel] = 255 - image.at<Vec3b>(y, x)[channel];
			}
		}
	}
}

Mat rgb2yiq(Mat & imageRGB)
{
	Mat imageYIQ = Mat::zeros(imageRGB.size(), imageRGB.type());

	int h = imageRGB.rows;
	int w = imageRGB.cols;

	int bB, bG, bR;
	int bY, bI, bQ;
	float fR, fG, fB;
	float fY, fI, fQ;
	const float FLOAT2BYTE = 255.0f;
	const float BYTE2FLOAT = 1.0f / FLOAT2BYTE;
	const float MIN_I = -0.5957f;
	const float MIN_Q = -0.5226f;
	const float Y2BYTE = 255.0f;
	const float I2BYTE = 255.0f / (MIN_I * -2.0f);
	const float Q2BYTE = 255.0f / (MIN_Q * -2.0f);

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			bB = imageRGB.at<Vec3b>(y, x)[0];
			bG = imageRGB.at<Vec3b>(y, x)[1];
			bR = imageRGB.at<Vec3b>(y, x)[2];

			fR = bR * BYTE2FLOAT;
			fG = bG * BYTE2FLOAT;
			fB = bG * BYTE2FLOAT;

			fY =	0.299 * fR +	0.587 * fG +	0.114 * fB;
			fI = 0.595716 * fR - 0.274453 * fG - 0.321263 * fB;
			fQ = 0.211456 * fR - 0.522591 * fG + 0.311135 * fB;

			bY = (int)(0.5f + fY * Y2BYTE);
			bI = (int)(0.5f + (fI - MIN_I) * I2BYTE);
			bQ = (int)(0.5f + (fQ - MIN_Q) * Q2BYTE);

			if (bY > 255)
				bY = 255;
			if (bY < 0)
				bY = 0;
			if (bI > 255)
				bI = 255;
			if (bI < 0)
				bI = 0;
			if (bQ > 255)
				bQ = 255;
			if (bQ < 0)
				bQ = 0;

			imageYIQ.at<Vec3b>(y, x)[0] = bY;
			imageYIQ.at<Vec3b>(y, x)[1] = bI;
			imageYIQ.at<Vec3b>(y, x)[2] = bQ;
		}
	}

	return imageYIQ;

}

Mat yiq2rgb(Mat & imageYIQ)
{
	Mat imageRGB = Mat::zeros(imageYIQ.size(), imageYIQ.type());

	int h = imageYIQ.rows;
	int w = imageYIQ.cols;

	int bB, bG, bR;
	int bY, bI, bQ;
	float fR, fG, fB;
	float fY, fI, fQ;
	const float FLOAT2BYTE = 255.0f;
	const float BYTE2FLOAT = 1.0f / FLOAT2BYTE;
	const float MIN_I = -0.5957f;
	const float MIN_Q = -0.5226f;
	const float Y2FLOAT = 1.0f / 255.0f;
	const float I2FLOAT = (MIN_I * -2.0f) / 255.0f;
	const float Q2FLOAT = (MIN_Q * -2.0f) / 255.0f;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			bY = imageYIQ.at<Vec3b>(y, x)[0];
			bI = imageYIQ.at<Vec3b>(y, x)[1];
			bQ = imageYIQ.at<Vec3b>(y, x)[2];

			fY = bY * Y2FLOAT;
			fI = bI * I2FLOAT + MIN_I;
			fQ = bQ * Q2FLOAT + MIN_Q;

			fR = fY + 0.9563 * fI + 0.6210 * fQ;
			fG = fY - 0.2721 * fI - 0.6474 * fQ;
			fB = fY - 1.1070 * fI + 1.7046 * fQ;

			bR = (int)(fR * FLOAT2BYTE);
			bG = (int)(fG * FLOAT2BYTE);
			bB = (int)(fB * FLOAT2BYTE);

			if (bR > 255)
				bR = 255;
			if (bR < 0)
				bR = 0;
			if (bG > 255)
				bG = 255;
			if (bG < 0)
				bG = 0;
			if (bB > 255)
				bB = 255;
			if (bB < 0)
				bB = 0;

			imageRGB.at<Vec3b>(y, x)[0] = bB;
			imageRGB.at<Vec3b>(y, x)[1] = bG;
			imageRGB.at<Vec3b>(y, x)[2] = bR;
		}
	}

	return imageRGB;

}