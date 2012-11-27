import java.awt.Color;

import junit.framework.TestCase;

/*
 * This testing framework provides basic level tests for 
 * each of the methods, however additional testing will be 
 * required, along with extensive testing of ALL helper methods
 * that you write.
 */
public class PictureTest extends TestCase {
	/*
	 * A method to test the private helper methods within
	 * Picture.java
	 */
	public void testHelpers() throws Exception
	{
		assertTrue(Picture.helpersWork());
		
	}
	/*
	 * Validate that grayscale works and does not modify the 
	 * original Picture object.
	 */
	public void testGrayscale()
	{
		Picture pic 		= Picture.loadPicture("Creek.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("Creek_grayscale.bmp");
		Picture picTest		= pic.grayscale();
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
	}
	/*
	 * Validate that negate works and does not modify the 
	 * original Picture object.
	 */
	public void testNegate()
	{
		Picture pic 		= Picture.loadPicture("Creek.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("Creek_negate.bmp");
		Picture picTest		= pic.negate();
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		pic = new Picture(5,5);
		Picture correct = new Picture(5,5);
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				pic.getPixel(i, j).setRed(0);
				pic.getPixel(i, j).setGreen(0);
				pic.getPixel(i, j).setBlue(0);
				correct.getPixel(i, j).setRed(255);
				correct.getPixel(i, j).setGreen(255);
				correct.getPixel(i, j).setBlue(255);
			}
		}
		pic.getPixel(0, 0).setRed(30);
		pic.getPixel(0, 0).setGreen(60);
		pic.getPixel(0, 0).setBlue(30);
		correct.getPixel(0,0).setRed(255-30);
		correct.getPixel(0,0).setGreen(255-60);
		correct.getPixel(0,0).setBlue(255-30);
		Picture test = pic.negate();
		assertTrue(correct.equals(test));
	}
	/*
	 * Validate that rotate(1) works and does not modify the 
	 * original Picture object.
	 */
	public void testRotate1()
	{
		Picture pic 		= Picture.loadPicture("CalOriginal.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("CalRotate1.bmp");
		Picture picTest		= pic.rotate(1);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a image that is a bar to be rotated
		pic = new Picture(10,1);
		Picture correct = new Picture(1,10);
		Picture test = pic.rotate(1);
		assertTrue(correct.equals(test));
	}

	/*
	 * Validate that rotate(2) works and does not modify the 
	 * original Picture object.
	 */
	public void testRotate2()
	{
		Picture pic 		= Picture.loadPicture("CalOriginal.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("CalRotate2.bmp");
		Picture picTest		= pic.rotate(2);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a image that is a bar to be rotated
		pic = new Picture(10,1);
		Picture correct = new Picture(10, 1);
		Picture test = pic.rotate(2);
		assertTrue(correct.equals(test));
	}

	/*
	 * Validate that rotate(3) works and does not modify the 
	 * original Picture object.
	 */
	public void testRotate3()
	{
		Picture pic 		= Picture.loadPicture("CalOriginal.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("CalRotate3.bmp");
		Picture picTest		= pic.rotate(3);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a image that is a bar to be rotated
		pic = new Picture(10,1);
		Picture correct = new Picture(1,10);
		Picture test = pic.rotate(3);
		assertTrue(correct.equals(test));
	}
	/*
	 * Validate that flip(Picture.HORIZONTAL) works and does not modify the 
	 * original Picture object.
	 */
	public void testFlipHorixontal() throws Exception
	{
		Picture pic 		= Picture.loadPicture("CalOriginal.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("CalHorizontal.bmp");
		Picture picTest		= pic.flip(Picture.HORIZONTAL);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a test image that is divided upper half black and lower half default for flipping
		Picture test = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 5; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		Picture correct = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 5; j < 10; j++){
				correct.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		test = test.flip(Picture.HORIZONTAL);
		assertTrue(test.equals(correct));
	}
	/*
	 * Validate that flip(Picture.VERTICAL) works and does not modify the 
	 * original Picture object.
	 */
	public void testFlipVertical() throws Exception
	{
		Picture pic 		= Picture.loadPicture("CalOriginal.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("CalVertical.bmp");
		Picture picTest		= pic.flip(Picture.VERTICAL);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a test image that is left half black and right half default for testing
		Picture test = new Picture(10, 10);
		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 10; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		
		Picture correct = new Picture(10, 10);
		for (int i = 5; i < 10; i++){
			for (int j = 0; j < 10; j++){
				correct.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		
		assertTrue(test.flip(Picture.VERTICAL).equals(correct));
	}
	/*
	 * Validate that flip(Picture.FORWARD_DIAGONAL) works and 
	 * does not modify the original Picture object.
	 */
	public void testFlipForwardDiagonal() throws Exception
	{
		Picture pic 		= Picture.loadPicture("CalOriginal.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("CalForwardDiagonal.bmp");
		Picture picTest		= pic.flip(Picture.FORWARD_DIAGONAL);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a test image that is split half black and half default along a forward slash to be flipped
		Picture test = new Picture(10, 10);
		int boundaryY = 10;
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < boundaryY; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
			boundaryY --;
		}
		Picture correct = new Picture(10, 10);
		int startY = 9;
		for (int i = 0; i < 10; i++){
			for (int j = startY; j < 10; j++){
				correct.getPixel(i,  j).setColor(Color.BLACK);
			}
			startY --;
		}
		
		assertTrue(test.flip(Picture.FORWARD_DIAGONAL).equals(correct));
	}
	/*
	 * Validate that flip(Picture.BACKWARD_DIAGONAL) works and 
	 * does not modify the original Picture object.
	 */
	public void testFlipBackwardDiagonal() throws Exception
	{
		Picture pic 		= Picture.loadPicture("CalOriginal.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("CalBackwardDiagonal.bmp");
		Picture picTest		= pic.flip(Picture.BACKWARD_DIAGONAL);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates an image that is half black and half default along a backwards slash to be flipped
		Picture test = new Picture(10, 10);
		int boundaryY = 0;
		for (int i = 0; i < 10; i++){
			for (int j = boundaryY; j < 10; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
			boundaryY ++;
		}
		Picture correct = new Picture(10, 10);
		int startY = 1;
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < startY; j++){
				correct.getPixel(i,  j).setColor(Color.BLACK);
			}
			startY ++;
		}
		
		assertTrue(test.flip(Picture.BACKWARD_DIAGONAL).equals(correct));
	}
	/*
	 * Validate that blur works and does not modify the 
	 * original Picture object.
	 */
	public void testBlur() throws Exception
	{
		Picture pic 		= Picture.loadPicture("Creek.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("Creek_blur.bmp");
		Picture picTest		= pic.blur(3);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a new 2x2 test image in which we know the rgb values. The correct image (threshold of 1)
		//should be of one color with the rgb being the averages of the test rgb.
		Picture test = new Picture(2, 2);
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				test.getPixel(i, j).setRed(0);
				test.getPixel(i, j).setGreen(0);
				test.getPixel(i, j).setBlue(0);
			}
		}
		test.getPixel(0, 0).setRed(40);
		test.getPixel(1, 1).setBlue(80);
		Picture correct = new Picture(2, 2);
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				correct.getPixel(i, j).setRed(10);
				correct.getPixel(i, j).setGreen(0);
				correct.getPixel(i, j).setBlue(20);
			}
		}
		assertTrue(test.blur(1).equals(correct));
		
	}
	/*
	 * Validate that showEdges works and does not modify the 
	 * original Picture object.
	 */
	public void testShowEdges() throws Exception
	{
		Picture pic 		= Picture.loadPicture("Colleen.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("Colleen_showEdges.bmp");
		Picture picTest		= pic.showEdges(20);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a test image that is divided upper half black and lower half default for finding the edge in between
		Picture test = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 5; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		Picture correct = new Picture(10,10);
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				correct.getPixel(i, j).setColor(Color.WHITE);
			}
		}
		for (int i = 0; i < 10; i++){
			correct.getPixel(i, 5).setColor(Color.BLACK);
		}
		assertTrue(test.showEdges(10).equals(correct));
	}
	/*
	 * Validate that chromaKey works and does not modify the 
	 * original Picture object.
	 */
	public void testChromaKey() throws Exception
	{
		Picture pic 		= Picture.loadPicture("Colleen.bmp");
		Picture bg 			= Picture.loadPicture("Creek.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("Colleen_chromaKey.bmp");
		Picture picTest		= pic.chromaKey(118, 54, bg, 30);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a new picture half black and half white that should be chromakeyed to all white
		Picture test = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 5; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		Picture background = new Picture(10,10);
		Picture correct = new Picture(10,10);
		assertTrue(test.chromaKey(1, 2, background, 10).equals(correct));
	}

	/*
	 * Tests the color changing a solid color:
	 * darken
	 */
	public void testColorTranslationsDarker() throws Exception
	{
		Picture pic = Picture.loadPicture("Gray.bmp");
		Picture darker = Picture.loadPicture("Gray_darker.bmp");
		assertTrue(darker.equals(pic.darken(30)));
			
	}
	/*
	 * Tests the color changing a solid color:
	 * lighten
	 */
	public void testColorTranslationsLighter() throws Exception
	{
		Picture pic = Picture.loadPicture("Gray.bmp");
		Picture lighter = Picture.loadPicture("Gray_lighter.bmp");
		assertTrue(lighter.equals(pic.lighten(30)));
			
	}
	/*
	 * Tests the color changing a solid color:
	 * addGreen
	 */
	public void testColorTranslationsGreener() throws Exception
	{
		Picture pic = Picture.loadPicture("Gray.bmp");
		Picture greener	= Picture.loadPicture("Gray_more_green.bmp");
		assertTrue(greener.equals(pic.addGreen(30)));
			
	}
	/*
	 * Tests the color changing a solid color:
	 * addBlue
	 */
	public void testColorTranslationsBluer() throws Exception
	{
		Picture pic = Picture.loadPicture("Gray.bmp");
		Picture bluer = Picture.loadPicture("Gray_more_blue.bmp");
		assertTrue(bluer.equals(pic.addBlue(30)));
			
	}
	/*
	 * Tests the color changing a solid color:
	 * addRed
	 */
	public void testColorTranslationsReder() throws Exception
	{
		Picture pic = Picture.loadPicture("Gray.bmp");
		Picture reder = Picture.loadPicture("Gray_more_red.bmp");
		assertTrue(reder.equals(pic.addRed(30)));	
			
	}
	/*
	 * Validate that paintBucket works and does not modify the 
	 * original Picture object.
	 */
	public void testPaintBucket()
	{
		Picture pic 		= Picture.loadPicture("Colleen.bmp");
		Picture picCopy 	= new Picture(pic);
		Picture picCorrect	= Picture.loadPicture("Colleen_paintBucket.bmp");
		Picture picTest		= pic.paintBucket(118, 54, 30, new Color(0, 255, 0));
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Creates a half black half white test image for filling in the black portion as green
		Picture test = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 5; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		Picture correct = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 5; j++){
				correct.getPixel(i,  j).setColor(Color.GREEN);
			}
		}
		assertTrue(test.paintBucket(1, 2, 10, Color.GREEN).equals(correct));
	}
	/*
	 * Validate that convertToAscii works and does not modify the 
	 * original Picture object.
	 */
	public void testConvertToAscii()
	{
		Picture pic         = Picture.loadPicture("mickey.bmp");
		Picture picCopy     = new Picture(pic);
		Picture picCorrect  = Picture.loadPicture("mickey_ascii.bmp");
		Picture picTest     = pic.convertToAscii();
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Tests for converting color blocks to ascii images in the helper test
		// Edge case cut off for ascii blocks over image boundary already tested in mickey image
	}
	/*
	 * Validate that showEdges works and does not modify the 
	 * original Picture object (and this picture is cute)
	 */
	public void testShowEdgesMickey() throws Exception
	{
		Picture pic         = Picture.loadPicture("mickey.bmp");
		Picture picCopy     = new Picture(pic);
		Picture picCorrect  = Picture.loadPicture("mickey_showEdges.bmp");
		Picture picTest     = pic.showEdges(20);
		assertTrue(pic.equals(picCopy));
		assertTrue(picCorrect.equals(picTest));
		
		// Individual color block to ascii image tests included in helper function test
	}
	/**
	 * Helper method for loading a picture in the current directory.
	 */
}
