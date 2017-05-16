#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <math.h>
#define GREEN_Y 140
#define GREEN_U -85
#define GREEN_V -100

void convert(int *p, float *yuv);

int isClose(float *yuv, int Y, int U, int V);

void on_trackbar (int val);
void on_mouse (int event, int x, int y, int flags, void* param);

IplImage *src_img = 0, *src_img_gray = 0, *tmp_img1 = 0;
IplImage *img = 0;
int Y = 128;
int U = 0;
int V = 0;

int
main (int argc, char **argv)
{
  int x, y;
  int p[3];
  IplImage *img;

  if (argc != 2 || (img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR)) == 0)
    return -1;

  // トラックバー作成
  cvCreateTrackbar ("Trackbar", "Image", 0, 255, on_trackbar);

  // マウスイベント設定
  cvSetMouseCallback ("Image", on_mouse);

  cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image", src_img);
  cvWaitKey (0);

  cvDestroyWindow ("Image");
  cvReleaseImage (&src_img);
  cvReleaseImage (&img);

  return 0;
}

void convert(int *p, float *array) {
  float Y, U, V;
  Y = 0.299 * p[2] + 0.587 * p[1] + 0.114 * p[0];
  U = -0.168736 * p[2] -0.331264 * p[1] + 0.5 * p[0];
  V = 0.5 * p[2] - 0.418688 * p[1] - 0.081312 * p[0];

  array[0] = Y;
  array[1] = U;
  array[2] = V;
}

int isClose(float *yuv, int Y, int U, int V) {
  float r;

  r = sqrt((yuv[0] - Y) * (yuv[0] - Y) + (yuv[1] - U) * (yuv[1] - U) + (yuv[2] - V) * (yuv[2] - V));
  if (r <= 20) {
    return 1;
  } else {
    return 0;
  }
}

/* コールバック関数 */
void
on_trackbar (int val)
{
  // (4)トラックバーの位置を取得
  Y = cvGetTrackbarPos ("Trackbar", "Image");

  // (1)画素値（R,G,B）を順次取得し，YUVに変換する
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      float yuv[3];

      /* 画素値を直接グレーに変更する */
      p[0] = img->imageData[img->widthStep * y + x * 3];        // B
      p[1] = img->imageData[img->widthStep * y + x * 3 + 1];    // G
      p[2] = img->imageData[img->widthStep * y + x * 3 + 2];    // R
      convert(p, yuv);

      if (isClose(yuv, Y, U, V)) {
        img->imageData[img->widthStep * y + x * 3] = cvRound (p[0]);      // B
        img->imageData[img->widthStep * y + x * 3 + 1] = cvRound (p[1]);  // G
        img->imageData[img->widthStep * y + x * 3 + 2] = cvRound (p[2]);  // R
      } else {
        img->imageData[img->widthStep * y + x * 3] = cvRound (0);      // B
        img->imageData[img->widthStep * y + x * 3 + 1] = cvRound (0);  // G
        img->imageData[img->widthStep * y + x * 3 + 2] = cvRound (0);  // R
      }


    }
  }

  // (6)トラックバー1の値を描画する
  cvShowImage ("Threshold", tmp_img1);

}

void
on_mouse (int event, int x, int y, int flags, void* param)
{

}

