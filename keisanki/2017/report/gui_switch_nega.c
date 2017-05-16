#include <cv.h>
#include <highgui.h>
#include <stdio.h>

/* グローバル変数 */
CvFont font;
IplImage *src_img = 0, *src_img_gray = 0, *tmp_img1 = 0;
IplImage *img = 0;

/* プロトタイプ宣言 */
void on_mouse (int event, int x, int y, int flags, void *param);

int
main (int argc, char **argv)
{
  char *str = "SWITCH";

  if (argc >= 2)
    src_img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR);
  if (src_img == 0)
    return -1;

  cvInitFont (&font, CV_FONT_HERSHEY_DUPLEX, 1.0, 1.0, 0.0, 1, CV_AA);
  cvRectangle (src_img, cvPoint (0, 0), cvPoint (200, 50), cvScalar (0, 0, 0, 0), CV_FILLED, 8, 0);
  cvPutText (src_img, str, cvPoint (15, 30), &font, CV_RGB (0, 200, 100));

  cvNot(src_img, src_img);

  cvNamedWindow ("SWITCH", CV_WINDOW_AUTOSIZE);

  cvShowImage ("SWITCH", src_img);

  cvSetMouseCallback ("SWITCH", on_mouse, 0);

  cvWaitKey (0);

  cvDestroyWindow ("SWITCH");
  cvReleaseImage (&src_img);

  return 0;
}

/* コールバック関数 */
void
on_mouse (int event, int x, int y, int flags, void *param)
{
  char *str = "SWITCH";

  if (event == CV_EVENT_LBUTTONDOWN && x >= 0 && x <= 200 && y >= 0 && y <= 50) {
    cvNot(src_img, src_img);
  }
  cvRectangle (src_img, cvPoint (0, 0), cvPoint (200, 50), cvScalar (0, 0, 0, 0), CV_FILLED, 8, 0);
  cvPutText (src_img, str, cvPoint (15, 30), &font, CV_RGB (0, 200, 100));
  cvShowImage ("SWITCH", src_img);
}
