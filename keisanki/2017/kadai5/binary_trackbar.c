#include <cv.h>
#include <highgui.h>
#include <stdio.h>

/* グローバル変数 */
CvFont font;
IplImage *src_img = 0, *src_img_gray = 0, *tmp_img1 = 0;
IplImage *img = 0;

/* プロトタイプ宣言 */
void on_trackbar (int val);

int
main (int argc, char **argv)
{

  // (1)画像を読み込む
  if (argc >= 2)
    src_img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR);
  if (src_img == 0)
    return -1;

  tmp_img1 = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  src_img_gray = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  cvCvtColor (src_img, src_img_gray, CV_BGR2GRAY);

  // (2)二値化:cvThreshold
  cvThreshold (src_img_gray, tmp_img1, 90, 255, CV_THRESH_BINARY);

  cvInitFont (&font, CV_FONT_HERSHEY_DUPLEX, 1.0, 1.0, 0.0, 1, CV_AA);
  cvRectangle (tmp_img1, cvPoint (0, 0), cvPoint (400, 50), cvScalar (0, 0, 0, 0), CV_FILLED, 8, 0);

  // (3)トラックバー用意
    // ウィンドウ作成
  cvNamedWindow ("Threshold", CV_WINDOW_AUTOSIZE);
    // トラックバー作成
  cvCreateTrackbar ("Trackbar", "Threshold", 0, 255, on_trackbar);

  cvShowImage ("Threshold", tmp_img1);
  cvWaitKey (0);

  cvDestroyWindow ("Threshold");
  cvReleaseImage (&src_img);
  cvReleaseImage (&src_img_gray);
  cvReleaseImage (&tmp_img1);

  return 0;
}

/* コールバック関数 */
void
on_trackbar (int val)
{
  char str[64];

  // (4)トラックバーの位置を取得
  int threshold;
  threshold = cvGetTrackbarPos ("Trackbar", "Threshold");

  // (5)二値化画像の描画
  cvThreshold (src_img_gray, tmp_img1, threshold, 255, CV_THRESH_BINARY);
  cvShowImage ("Threshold", tmp_img1);

  // (6)トラックバー1の値を描画する
  cvRectangle (tmp_img1, cvPoint (0, 0), cvPoint (400, 50), cvScalar (0, 0, 0, 0), CV_FILLED, 8, 0);
  snprintf (str, 64, "%d", val);
  cvPutText (tmp_img1, str, cvPoint (15, 30), &font, CV_RGB (0, 200, 100));
  cvShowImage ("Threshold", tmp_img1);

}
