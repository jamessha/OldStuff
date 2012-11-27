import java.awt.*;
import java.net.URL;
import java.util.*;

;

/**
 * A class that represents a picture. This class inherits from SimplePicture and
 * allows the student to add functionality and picture effects.
 * 
 * @author Barb Ericson (ericson@cc.gatech.edu) (Copyright Georgia Institute of
 *         Technology 2004)
 * @author Modified by Colleen Lewis (colleenl@berkeley.edu), Jonathan Kotker
 *         (jo_ko_berkeley@berkeley.edu), Kaushik Iyer (kiyer@berkeley.edu),
 *         George Wang (georgewang@berkeley.edu), and David Zeng
 *         (davidzeng@berkeley.edu), for use in CS61BL, the data structures
 *         course at University of California, Berkeley.
 */
public class Picture extends SimplePicture {

	// ///////////////////////// Static Variables //////////////////////////////

	// Different axes available to flip a picture.
	public static final int HORIZONTAL = 1;
	public static final int VERTICAL = 2;
	public static final int FORWARD_DIAGONAL = 3;
	public static final int BACKWARD_DIAGONAL = 4;

	// Different Picture objects for the bitmaps used in ASCII art conversion.
	private static Picture BMP_AMPERSAND;
	private static Picture BMP_APOSTROPHE;
	private static Picture BMP_AT;
	private static Picture BMP_BAR;
	private static Picture BMP_COLON;
	private static Picture BMP_DOLLAR;
	private static Picture BMP_DOT;
	private static Picture BMP_EXCLAMATION;
	private static Picture BMP_GRAVE;
	private static Picture BMP_HASH;
	private static Picture BMP_PERCENT;
	private static Picture BMP_SEMICOLON;
	private static Picture BMP_SPACE;
	
	// ////////////////////////// Constructors /////////////////////////////////

	/**
	 * A constructor that takes no arguments.
	 */
	public Picture() {
		super();
	}

	/**
	 * Creates a Picture from the file name provided.
	 * 
	 * @param fileName
	 *            The name of the file to create the picture from.
	 */
	public Picture(String fileName) {
		// Let the parent class handle this fileName.
		super(fileName);
	}

	/**
	 * Creates a Picture from the width and height provided.
	 * 
	 * @param width
	 *            the width of the desired picture.
	 * @param height
	 *            the height of the desired picture.
	 */
	public Picture(int width, int height) {
		// Let the parent class handle this width and height.
		super(width, height);
	}

	/**
	 * Creates a copy of the Picture provided.
	 * 
	 * @param pictureToCopy
	 *            Picture to be copied.
	 */
	public Picture(Picture pictureToCopy) {
		// Let the parent class do the copying.
		super(pictureToCopy);
	}

	/**
	 * Creates a copy of the SimplePicture provided.
	 * 
	 * @param pictureToCopy
	 *            SimplePicture to be copied.
	 */
	public Picture(SimplePicture pictureToCopy) {
		// Let the parent class do the copying.
		super(pictureToCopy);
	}

	// ///////////////////////////// Methods ///////////////////////////////////

	/**
	 * @return A string with information about the picture, such as filename,
	 *         height, and width.
	 */
	public String toString() {
		String output = "Picture, filename = " + this.getFileName() + ","
				+ " height = " + this.getHeight() + ", width = "
				+ this.getWidth();
		return output;
	}

	// ///////////////////// PROJECT 1 BEGINS HERE /////////////////////////////

	/*
	 * Each of the methods below is constructive: in other words, each of the
	 * methods below generates a new Picture, without permanently modifying the
	 * original Picture.
	 */

	// ////////////////////////////// Level 1 //////////////////////////////////

	/**
	 * Converts the Picture into grayscale. Since any variation of gray is
	 * obtained by setting the red, green, and blue components to the same
	 * value, a Picture can be converted into its grayscale component by setting
	 * the red, green, and blue components of each pixel in the new picture to
	 * the same value: the average of the red, green, and blue components of the
	 * same pixel in the original.
	 * 
	 * @return A new Picture that is the grayscale version of this Picture.
	 */
	public Picture grayscale() {
		Picture newPicture = new Picture(this);

		int pictureHeight = this.getHeight();
		int pictureWidth = this.getWidth();

		for (int x = 0; x < pictureWidth; x++) {
			for (int y = 0; y < pictureHeight; y++) {
				newPicture.setPixelToGray(x, y);
			}
		}
		return newPicture;
	}

	/**
	 * Helper method for grayscale() to set a pixel at (x, y) to be gray.
	 * 
	 * @param x
	 *            The x-coordinate of the pixel to be set to gray.
	 * @param y
	 *            The y-coordinate of the pixel to be set to gray.
	 */
	private void setPixelToGray(int x, int y) {
		Pixel currentPixel = this.getPixel(x, y);
		int average = currentPixel.getAverage();
		currentPixel.setRed(average);
		currentPixel.setGreen(average);
		currentPixel.setBlue(average);
	}

	/**
	 * Test method for setPixelToGray. This method is called by the JUnit file
	 * through the public method Picture.helpersWork().
	 */
	private static boolean setPixelToGrayWorks() {
		Picture bg = Picture.loadPicture("Creek.bmp");
		Pixel focalPixel = bg.getPixel(10, 10);
		bg.setPixelToGray(10, 10);
		int goalColor = (int) focalPixel.getAverage();
		int originalAlpha = focalPixel.getColor().getAlpha();
		boolean redCorrect = focalPixel.getRed() == goalColor;
		boolean greenCorrect = focalPixel.getGreen() == goalColor;
		boolean blueCorrect = focalPixel.getBlue() == goalColor;
		boolean alphaCorrect = focalPixel.getAlpha() == originalAlpha;
		return redCorrect && greenCorrect && blueCorrect && alphaCorrect;
	}

	/**
	 * This method provide JUnit access to the testing methods written within
	 * Picture.java
	 * @throws IllegalArgumentIllegalArgumentException 
	 */
	public static boolean helpersWork() throws IllegalArgumentException {
		if (!Picture.setPixelToGrayWorks()) {
			return false;
		}
		if (!Picture.negatePixelWorks()) {
			return false;
		}
		if (!Picture.lightenPixelWorks()) {
			return false;
		}
		if (!Picture.darkenPixelWorks()) {
			return false;
		}
		if (!Picture.addBluePixelWorks()) {
			return false;
		}
		if (!Picture.addRedPixelWorks()) {
			return false;
		}
		if (!Picture.addGreenPixelWorks()) {
			return false;
		}
		if (!Picture.chromaKeyPixelWorks()) {
			return false;
		}
		if (!Picture.rotatePixelWorks()) {
			return false;
		}
		if (!Picture.flipPixelWorks()) {
			return false;
		}
		if (!Picture.edgePixelWorks()) {
			return false;
		}
		if (!Picture.asciiPixelWorks()) {
			return false;
		}
		if (!Picture.blurPixelWorks()) {
			return false;
		}

		// You could put other tests here..

		return true;
	}

	/**
	 * Converts the Picture into its photonegative version. The photonegative
	 * version of an image is obtained by setting each of the red, green, and
	 * blue components of every pixel to a value that is 255 minus their current
	 * values.
	 * 
	 * @return A new Picture that is the photonegative version of this Picture.
	 */
	public Picture negate() {
		// REPLACE THE CODE BELOW WITH YOUR OWN.
		Picture newPicture = new Picture(this);

		int pictureHeight = this.getHeight();
		int pictureWidth = this.getWidth();

		for (int x = 0; x < pictureWidth; x++) {
			for (int y = 0; y < pictureHeight; y++) {
				newPicture.negatePixel(x, y);
			}
		}

		return newPicture;
	}

	/**
	 * Helper method for negate() to set a pixel at (x, y) to be set to its
	 * photonegative.
	 * 
	 * @param x
	 *            The x-coordinate of the pixel to be set to its photonegative.
	 * @param y
	 *            The y-coordinate of the pixel to be set to its photonegative.
	 */
	private void negatePixel(int x, int y) {
		Pixel currentPixel = this.getPixel(x, y);
		int currentRed = currentPixel.getRed();
		int currentBlue = currentPixel.getBlue();
		int currentGreen = currentPixel.getGreen();
		currentPixel.setRed(255 - currentRed);
		currentPixel.setBlue(255 - currentBlue);
		currentPixel.setGreen(255 - currentGreen);
	}

	/**
	 * Test case for the helper function negatePixel. Ensures that the RGB value
	 * of each pixel is that of (255 - original RGB)
	 */
	private static boolean negatePixelWorks() {
		Picture bn = Picture.loadPicture("Creek.bmp");
		Pixel focalPixel = bn.getPixel(10, 10);
		int goalRed = ((int) 255 - focalPixel.getRed());
		int goalGreen = ((int) 255 - focalPixel.getGreen());
		int goalBlue = ((int) 255 - focalPixel.getBlue());
		bn.negatePixel(10, 10);
		int originalAlpha = focalPixel.getColor().getAlpha();
		boolean redCorrect = focalPixel.getRed() == goalRed;
		boolean greenCorrect = focalPixel.getGreen() == goalGreen;
		boolean blueCorrect = focalPixel.getBlue() == goalBlue;
		boolean alphaCorrect = focalPixel.getAlpha() == originalAlpha;
		return redCorrect && greenCorrect && blueCorrect && alphaCorrect;
	}

	/**
	 * Creates an image that is lighter than the original image. The range of
	 * each color component should be between 0 and 255 in the new image. The
	 * alpha value should not be changed.
	 * 
	 * @return A new Picture that has every color value of the Picture increased
	 *         by the lightenAmount.
	 * @throws IllegalArgumentException 
	 */
	public Picture lighten(int lightenAmount) throws IllegalArgumentException {
		// REPLACE THE CODE BELOW WITH YOUR OWN.
		if (lightenAmount > 255 || lightenAmount < 0){
			throw new IllegalArgumentException("You're trying to lighten by an amount over 255 or under 0... try again");
		}
		Picture newPicture = new Picture(this);

		int pictureHeight = this.getHeight();
		int pictureWidth = this.getWidth();

		for (int x = 0; x < pictureWidth; x++) {
			for (int y = 0; y < pictureHeight; y++) {
				newPicture.lightenPixel(x, y, lightenAmount);
			}
		}

		return newPicture;
	}

	/**
	 * Helper method for lighten() to lighten a pixel at (x, y).
	 * 
	 * @param x
	 *            The x-coordinate of the pixel to be lightened.
	 * @param y
	 *            The y-coordinate of the pixel to be lightened.
	 * @throws IllegalArgumentException 
	 */
	private void lightenPixel(int x, int y, int amount) throws IllegalArgumentException {
		Pixel currentPixel = this.getPixel(x, y);
		int currentRed = currentPixel.getRed();
		int currentBlue = currentPixel.getBlue();
		int currentGreen = currentPixel.getGreen();
		if(currentRed + amount > 255 || currentGreen + amount > 255 || currentBlue + amount > 255){
			throw new IllegalArgumentException("Lightening by this amount will cause one of the colors to go over a value of 255, try again");
		}
		currentPixel.setRed(currentRed + amount);
		currentPixel.setBlue(currentBlue + amount);
		currentPixel.setGreen(currentGreen + amount);
	}

	/**
	 * Test case for the helper function lightenPixel(). Ensures that the RGB
	 * value of each pixel is that of (original RGB + 50) and that lightening by
	 * -50 returns the pixel to the original color
	 * @throws IllegalArgumentException 
	 */
	private static boolean lightenPixelWorks() throws IllegalArgumentException {
		Picture bn = Picture.loadPicture("Creek.bmp");
		Pixel focalPixel = bn.getPixel(10, 10);
		int originalAlpha = focalPixel.getColor().getAlpha();
		int origRed = (int) focalPixel.getRed();
		int origGreen = (int) focalPixel.getGreen();
		int origBlue = (int) focalPixel.getBlue();
		int goalRed = ((int) focalPixel.getRed() + 50);
		int goalGreen = ((int) focalPixel.getGreen() + 50);
		int goalBlue = ((int) focalPixel.getBlue() + 50);
		// Lightening the pixel by 0 points
		bn.lightenPixel(10, 10, 0);
		boolean redCorrect = focalPixel.getRed() == origRed;
		boolean greenCorrect = focalPixel.getGreen() == origGreen;
		boolean blueCorrect = focalPixel.getBlue() == origBlue;
		// Lightening the pixel by 50 points
		bn.lightenPixel(10, 10, 50);
		boolean redCorrect1 = focalPixel.getRed() == goalRed;
		boolean greenCorrect1 = focalPixel.getGreen() == goalGreen;
		boolean blueCorrect1 = focalPixel.getBlue() == goalBlue;
		// Lightening the pixel by -50 points
		bn.lightenPixel(10, 10, -50);
		boolean redCorrect2 = focalPixel.getRed() == origRed;
		boolean greenCorrect2 = focalPixel.getGreen() == origGreen;
		boolean blueCorrect2 = focalPixel.getBlue() == origBlue;
		boolean alphaCorrect = focalPixel.getAlpha() == originalAlpha;
		return redCorrect && greenCorrect && blueCorrect && redCorrect1
				&& greenCorrect1 && blueCorrect1 && redCorrect2
				&& greenCorrect2 && blueCorrect2 && alphaCorrect;
	}

	/**
	 * Creates an image that is darker than the original image.The range of each
	 * color component should be between 0 and 255 in the new image. The alpha
	 * value should not be changed.
	 * 
	 * @return A new Picture that has every color value of the Picture decreased
	 *         by the darkenenAmount.
	 * @throws IllegalArgumentException 
	 */
	public Picture darken(int darkenAmount) throws IllegalArgumentException {
		// REPLACE THE CODE BELOW WITH YOUR OWN.
		if (darkenAmount > 255 || darkenAmount < 0){
			throw new IllegalArgumentException("You're trying to darken by an amount over 255 or under 0... try again");
		}
		Picture newPicture = new Picture(this);

		int pictureHeight = this.getHeight();
		int pictureWidth = this.getWidth();

		for (int x = 0; x < pictureWidth; x++) {
			for (int y = 0; y < pictureHeight; y++) {
				newPicture.darkenPixel(x, y, darkenAmount);
			}
		}

		return newPicture;
	}

	/**
	 * Helper method for darken() to darken a pixel at (x, y).
	 * 
	 * @param x
	 *            The x-coordinate of the pixel to be darkened.
	 * @param y
	 *            The y-coordinate of the pixel to be darkened.
	 * @throws IllegalArgumentException 
	 */
	private void darkenPixel(int x, int y, int amount) throws IllegalArgumentException {
		Pixel currentPixel = this.getPixel(x, y);
		int currentRed = currentPixel.getRed();
		int currentBlue = currentPixel.getBlue();
		int currentGreen = currentPixel.getGreen();
		if(currentRed - amount < 0|| currentGreen - amount < 0 || currentBlue - amount < 0){
			throw new IllegalArgumentException("Darkening by this amount will cause one of the colors to go under a value of 0, try again");
		}
		currentPixel.setRed(currentRed - amount);
		currentPixel.setBlue(currentBlue - amount);
		currentPixel.setGreen(currentGreen - amount);
	}

	/**
	 * Test case for the helper function darkenPixel(). Ensures that the RGB
	 * value of each pixel is that of (original RGB - 50) and that darkening by
	 * -50 returns the pixel to the original color
	 * @throws IllegalArgumentException 
	 */
	private static boolean darkenPixelWorks() throws IllegalArgumentException {
		Picture bn = Picture.loadPicture("Creek.bmp");
		Pixel focalPixel = bn.getPixel(10, 10);
		int originalAlpha = focalPixel.getColor().getAlpha();
		int origRed = (int) focalPixel.getRed();
		int origGreen = (int) focalPixel.getGreen();
		int origBlue = (int) focalPixel.getBlue();
		int goalRed = ((int) focalPixel.getRed() - 50);
		int goalGreen = ((int) focalPixel.getGreen() - 50);
		int goalBlue = ((int) focalPixel.getBlue() - 50);
		// Darkening the pixel by 0 points
		bn.darkenPixel(10, 10, 0);
		boolean redCorrect = focalPixel.getRed() == origRed;
		boolean greenCorrect = focalPixel.getGreen() == origGreen;
		boolean blueCorrect = focalPixel.getBlue() == origBlue;
		// Darkening the pixel by 50 points
		bn.darkenPixel(10, 10, 50);
		boolean redCorrect1 = focalPixel.getRed() == goalRed;
		boolean greenCorrect1 = focalPixel.getGreen() == goalGreen;
		boolean blueCorrect1 = focalPixel.getBlue() == goalBlue;
		// Darkening the pixel by -50 points
		bn.darkenPixel(10, 10, -50);
		boolean redCorrect2 = focalPixel.getRed() == origRed;
		boolean greenCorrect2 = focalPixel.getGreen() == origGreen;
		boolean blueCorrect2 = focalPixel.getBlue() == origBlue;
		boolean alphaCorrect = focalPixel.getAlpha() == originalAlpha;
		return redCorrect && greenCorrect && blueCorrect && redCorrect1
				&& greenCorrect1 && blueCorrect1 && redCorrect2
				&& greenCorrect2 && blueCorrect2 && alphaCorrect;
	}

	/**
	 * Creates an image where the blue value has been increased by amount.The
	 * range of each color component should be between 0 and 255 in the new
	 * image. The alpha value should not be changed.
	 * 
	 * @return A new Picture that has every blue value of the Picture increased
	 *         by amount.
	 * @throws IllegalArgumentException 
	 */
	public Picture addBlue(int amount) throws IllegalArgumentException {
		// REPLACE THE CODE BELOW WITH YOUR OWN.
		if (amount > 255 || amount < 0){
			throw new IllegalArgumentException("You're trying to add a value over 255 or under 0... try again");
		}
		Picture newPicture = new Picture(this);

		int pictureHeight = this.getHeight();
		int pictureWidth = this.getWidth();

		for (int x = 0; x < pictureWidth; x++) {
			for (int y = 0; y < pictureHeight; y++) {
				newPicture.addBluePixel(x, y, amount);
			}
		}

		return newPicture;
	}

	/**
	 * Helper method for addBlue() to add blue to a pixel at (x, y).
	 * 
	 * @param x
	 *            The x-coordinate of the pixel to add blue to.
	 * @param y
	 *            The y-coordinate of the pixel to add blue to.
	 * @throws IllegalArgumentException 
	 */
	private void addBluePixel(int x, int y, int amount) throws IllegalArgumentException {
		Pixel currentPixel = this.getPixel(x, y);
		int currentBlue = currentPixel.getBlue();
		if(currentBlue + amount > 255){
			throw new IllegalArgumentException("Adding this amount will cause one of the colors to go over a value of 255, try again");
		}
		currentPixel.setBlue(currentBlue + amount);
	}

	/**
	 * Test case for the helper function addBluePixel(). Ensures that the blue
	 * value of each pixel is that of (original blue + 50) and that adding
	 * another -50 blue returns the pixel to the original color
	 * @throws IllegalArgumentException 
	 */
	private static boolean addBluePixelWorks() throws IllegalArgumentException {
		Picture bn = Picture.loadPicture("Creek.bmp");
		Pixel focalPixel = bn.getPixel(10, 10);
		int originalAlpha = focalPixel.getColor().getAlpha();
		int origBlue = (int) focalPixel.getBlue();
		int goalBlue = ((int) focalPixel.getBlue() + 50);
		// Blueifying the pixel by 0 points
		bn.addBluePixel(10, 10, 0);
		boolean blueCorrect = focalPixel.getBlue() == origBlue;
		// Blueifying the pixel by 50 points
		bn.addBluePixel(10, 10, 50);
		boolean blueCorrect1 = focalPixel.getBlue() == goalBlue;
		// Blueifying the pixel by -50 points
		bn.addBluePixel(10, 10, -50);
		boolean blueCorrect2 = focalPixel.getBlue() == origBlue;
		boolean alphaCorrect = focalPixel.getAlpha() == originalAlpha;
		return blueCorrect && blueCorrect1 && blueCorrect2 && alphaCorrect;
	}

	/**
	 * Creates an image where the red value has been increased by amount. The
	 * range of each color component should be between 0 and 255 in the new
	 * image. The alpha value should not be changed.
	 * 
	 * @return A new Picture that has every red value of the Picture increased
	 *         by amount.
	 * @throws IllegalArgumentException 
	 */
	public Picture addRed(int amount) throws IllegalArgumentException {
		// REPLACE THE CODE BELOW WITH YOUR OWN.
		if (amount > 255 || amount < 0){
			throw new IllegalArgumentException("You're trying to add a value over 255 or under 0... try again");
		}
		Picture newPicture = new Picture(this);

		int pictureHeight = this.getHeight();
		int pictureWidth = this.getWidth();

		for (int x = 0; x < pictureWidth; x++) {
			for (int y = 0; y < pictureHeight; y++) {
				newPicture.addRedPixel(x, y, amount);
			}
		}

		return newPicture;
	}

	/**
	 * Helper method for addRed() to add red to a pixel at (x, y).
	 * 
	 * @param x
	 *            The x-coordinate of the pixel to add red to.
	 * @param y
	 *            The y-coordinate of the pixel to add red to.
	 * @throws IllegalArgumentException 
	 */
	private void addRedPixel(int x, int y, int amount) throws IllegalArgumentException {
		Pixel currentPixel = this.getPixel(x, y);
		int currentRed = currentPixel.getRed();
		if(currentRed + amount > 255){
			throw new IllegalArgumentException("Adding this amount will cause one of the colors to go over a value of 255, try again");
		}
		currentPixel.setRed(currentRed + amount);
	}

	/**
	 * Test case for the helper function addRedPixel(). Ensures that the red
	 * value of each pixel is that of (original red + 50) and that adding
	 * another -50 red returns the pixel to the original color
	 * @throws IllegalArgumentException 
	 */
	private static boolean addRedPixelWorks() throws IllegalArgumentException {
		Picture bn = Picture.loadPicture("Creek.bmp");
		Pixel focalPixel = bn.getPixel(10, 10);
		int originalAlpha = focalPixel.getColor().getAlpha();
		int origRed = (int) focalPixel.getRed();
		int goalRed = ((int) focalPixel.getRed() + 50);
		// Redifying the pixel by 0 points
		bn.addRedPixel(10, 10, 0);
		boolean redCorrect = focalPixel.getRed() == origRed;
		// Redifying the pixel by 50 points
		bn.addRedPixel(10, 10, 50);
		boolean redCorrect1 = focalPixel.getRed() == goalRed;
		// Redifying the pixel by -50 points
		bn.addRedPixel(10, 10, -50);
		boolean redCorrect2 = focalPixel.getRed() == origRed;
		boolean alphaCorrect = focalPixel.getAlpha() == originalAlpha;
		return redCorrect && redCorrect1 && redCorrect2 && alphaCorrect;
	}

	/**
	 * Creates an image where the green value has been increased by amount. The
	 * range of each color component should be between 0 and 255 in the new
	 * image. The alpha value should not be changed.
	 * 
	 * @return A new Picture that has every green value of the Picture increased
	 *         by amount.
	 * @throws IllegalArgumentException 
	 */
	public Picture addGreen(int amount) throws IllegalArgumentException {
		// REPLACE THE CODE BELOW WITH YOUR OWN.
		if (amount > 255 || amount < 0){
			throw new IllegalArgumentException("You're trying to add a value over 255 or under 0... try again");
		}
		Picture newPicture = new Picture(this);

		int pictureHeight = this.getHeight();
		int pictureWidth = this.getWidth();

		for (int x = 0; x < pictureWidth; x++) {
			for (int y = 0; y < pictureHeight; y++) {
				newPicture.addGreenPixel(x, y, amount);
			}
		}

		return newPicture;
	}

	/**
	 * Helper method for addBlue() to add green to a pixel at (x, y).
	 * 
	 * @param x
	 *            The x-coordinate of the pixel to add green to.
	 * @param y
	 *            The y-coordinate of the pixel to add green to.
	 * @throws IllegalArgumentException 
	 */
	private void addGreenPixel(int x, int y, int amount) throws IllegalArgumentException {
		Pixel currentPixel = this.getPixel(x, y);
		int currentGreen = currentPixel.getGreen();
		if(currentGreen + amount > 255){
			throw new IllegalArgumentException("Adding this amount will cause one of the colors to go over a value of 255, try again");
		}
		currentPixel.setGreen(currentGreen + amount);
	}

	/**
	 * Test case for the helper function addGreenPixel(). Ensures that the green
	 * value of each pixel is that of (original green + 50) and that adding
	 * another -50 green returns the pixel to the original color
	 * @throws IllegalArgumentException 
	 */
	private static boolean addGreenPixelWorks() throws IllegalArgumentException {
		Picture bn = Picture.loadPicture("Creek.bmp");
		Pixel focalPixel = bn.getPixel(10, 10);
		int originalAlpha = focalPixel.getColor().getAlpha();
		int origGreen = (int) focalPixel.getGreen();
		int goalGreen = ((int) focalPixel.getGreen() + 50);
		// Greenifying the pixel by 0 points
		bn.addGreenPixel(10, 10, 0);
		boolean greenCorrect = focalPixel.getGreen() == origGreen;
		// Greenifying the pixel by 50 points
		bn.addGreenPixel(10, 10, 50);
		boolean greenCorrect1 = focalPixel.getGreen() == goalGreen;
		// Greenifying the pixel by -50 points
		bn.addGreenPixel(10, 10, -50);
		boolean greenCorrect2 = focalPixel.getGreen() == origGreen;
		boolean alphaCorrect = focalPixel.getAlpha() == originalAlpha;
		return greenCorrect && greenCorrect1 && greenCorrect2 && alphaCorrect;
	}

	/**
	 * @param x
	 *            x-coordinate of the pixel currently selected.
	 * @param y
	 *            y-coordinate of the pixel currently selected.
	 * @param background
	 *            Picture to use as the background.
	 * @param threshold
	 *            Threshold within which to replace pixels.
	 * 
	 * @return A new Picture where all the pixels in the original Picture, which
	 *         differ from the currently selected pixel within the provided
	 *         threshold (in terms of color distance), are replaced with the
	 *         corresponding pixels in the background picture provided.
	 * 
	 *         If the two Pictures are of different dimensions, the new Picture
	 *         will have length equal to the smallest of the two Pictures being
	 *         combined, and height equal to the smallest of the two Pictures
	 *         being combined. In this case, the Pictures are combined as if
	 *         they were aligned at the top left corner (0, 0).
	 * @throws IllegalArgumentException 
	 */
	public Picture chromaKey(int xRef, int yRef, Picture background,
			int threshold) throws IllegalArgumentException {
		if(!this.inRange(xRef, yRef)){
			throw new IllegalArgumentException("Your reference points are outside the picture... how did you manage to do this?");
		}

		int height1 = this.getHeight();
		int width1 = this.getWidth();
		int height2 = background.getHeight();
		int width2 = background.getWidth();
		int height;
		int width;
		if (height1 < height2)
			height = height1;
		else
			height = height2;
		if (width1 < width2)
			width = width1;
		else
			width = width2;

		Pixel refPixel = this.getPixel(xRef, yRef);
		Color refColor = refPixel.getColor();

		Picture newPicture = new Picture(width, height);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				newPicture.chromaKeyPixel(x, y, this, background, threshold,
						refColor);
			}
		}
		return newPicture;
	}

	// Helper function that checks if the pixel on the original is within the
	// theshold, copying it into the new picture if it is and copying that of
	// the background to the new picture if not
	private void chromaKeyPixel(int x, int y, Picture original,
			Picture background, int threshold, Color refColor) {
		Pixel origPixel = original.getPixel(x, y);
		Pixel backPixel = background.getPixel(x, y);
		Color origColor = origPixel.getColor();
		Color backColor = backPixel.getColor();
		Pixel newPicturePixel = this.getPixel(x, y);
		if (origPixel.colorDistance(refColor) <= threshold)
			newPicturePixel.setColor(backColor);
		else
			newPicturePixel.setColor(origColor);
	}

	/**
	 * Test case for the helper function chromaKeyPixel, determines if the pixel
	 * at (118, 54) of colleen is set to the corresponding pixel from creek
	 */
	private static boolean chromaKeyPixelWorks() {
		Picture background = Picture.loadPicture("Creek.bmp");
		Picture original = Picture.loadPicture("Colleen.bmp");
		Pixel origPixel = original.getPixel(118, 54);
		Pixel backPixel = background.getPixel(118, 54);
		Color origColor = origPixel.getColor();
		Color backColor = backPixel.getColor();
		Picture newPicture = new Picture(original);
		Pixel focalPixel = newPicture.getPixel(118, 54);
		int originalAlpha = origPixel.getColor().getAlpha();
		newPicture.chromaKeyPixel(118, 54, original, background, 30, origColor);
		boolean pixelCorrect = focalPixel.colorDistance(backColor) == 0;
		boolean alphaCorrect = focalPixel.getAlpha() == originalAlpha;
		return pixelCorrect && alphaCorrect;
	}

	// ////////////////////////////// Level 2 //////////////////////////////////

	/**
	 * Rotates this Picture by the integer multiple of 90 degrees provided. If
	 * the number of rotations provided is positive, then the picture is rotated
	 * clockwise; else, the picture is rotated counterclockwise. Multiples of
	 * four rotations (including zero) correspond to no rotation at all.
	 * 
	 * @param rotations
	 *            The number of 90-degree rotations to rotate this image by.
	 * 
	 * @return A new Picture that is the rotated version of this Picture.
	 */
	public Picture rotate(int rotations) {
		// REPLACE THE CODE BELOW WITH YOUR OWN.
		boolean inverse = false;
		if (rotations < 0) {
			inverse = true;
			rotations = rotations * (-1);
		}
		Picture oldPicture = new Picture(this);
		Picture newPicture = new Picture(this);
		for (int i = 0; i < rotations; i++) {
			int width = newPicture.getWidth();
			int height = newPicture.getHeight();
			newPicture = new Picture(height, width);
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					newPicture.rotatePixels(x, y, oldPicture, inverse);
				}
			}
			oldPicture = newPicture;
		}
		return newPicture;
	}

	// Helper function for rotate() that places a pixel into its rotated
	// position
	private void rotatePixels(int x, int y, Picture oldPicture, boolean inverse) {
		int height = oldPicture.getHeight();
		int width = oldPicture.getWidth();
		Pixel oldPixel = oldPicture.getPixel(x, y);
		Pixel newPixel;
		if (!inverse) {
			newPixel = this.getPixel(height - y - 1, x);
		} else {
			newPixel = this.getPixel(y, width - x - 1);
		}
		Color oldColor = oldPixel.getColor();
		newPixel.setColor(oldColor);
	}
	
	/**
	 * Test case for the helper function rotatePixel(). Ensures when a half black half 
	 * white image is rotated at a point such that a white pixel must turn black, 
	 * the proper pixel is turned black
	 */
	private static boolean rotatePixelWorks() {
		/* Creates a new 10 by 10 test image, upper half black and lower half white
		 *   __________
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |          |
		 *  |          |
		 *  |          |
		 *  |          |
		 *  |__________|
		 */
		Picture test = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 6; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		Picture test2 = new Picture(test);
		test2.rotatePixels(7, 2, test, false);
		boolean rotate1 = (test2.getPixel(7, 7).colorDistance(Color.BLACK) == 0);
		Picture test3 = new Picture(test);
		test3.rotatePixels(2,  2, test, true);
		boolean rotate2 = (test3.getPixel(2, 7).colorDistance(Color.BLACK) == 0);
		return rotate1 && rotate2;
	}

	/**
	 * Flips this Picture about the given axis. The axis can be one of four
	 * static integer constants:
	 * 
	 * (a) Picture.HORIZONTAL: The picture should be flipped about a horizontal
	 * axis passing through the center of the picture. (b) Picture.VERTICAL: The
	 * picture should be flipped about a vertical axis passing through the
	 * center of the picture. (c) Picture.FORWARD_DIAGONAL: The picture should
	 * be flipped about an axis that passes through the north-east and
	 * south-west corners of the picture. (d) Picture.BACKWARD_DIAGONAL: The
	 * picture should be flipped about an axis that passes through the
	 * north-west and south-east corners of the picture.
	 * 
	 * @param axis
	 *            Axis about which to flip the Picture provided.
	 * 
	 * @return A new Picture flipped about the axis provided.
	 * @throws IllegalArgumentException 
	 */
	public Picture flip(int axis) throws IllegalArgumentException {
		// REPLACE THE CODE BELOW WITH YOUR OWN.
		if(axis < 1 || axis > 4){
			throw new IllegalArgumentException("Your chosen axis does not exist... try again");
		}
		Picture newPicture = new Picture(this);
		int width = this.getWidth();
		int height = this.getHeight();
		if (axis == 1) {
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					newPicture.flipPixel1(x, y, this, height);
				}
			}
		}
		if (axis == 2) {
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					newPicture.flipPixel2(x, y, this, width);
				}
			}
		}
		if (axis == 3) {
			newPicture = new Picture(height, width);
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					newPicture.flipPixel3(x, y, this, width, height);
				}
			}
		}
		if (axis == 4) {
			newPicture = new Picture(height, width);
			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					newPicture.flipPixel4(x, y, this, width, height);
				}
			}
		}

		return newPicture;
	}

	// Helper function for flipping pixels along a horizontal axis
	private void flipPixel1(int x, int y, Picture original, int height) {
		Pixel origPixel = original.getPixel(x, y);
		Color origColor = origPixel.getColor();
		Pixel newPixel = this.getPixel(x, height - y - 1);
		newPixel.setColor(origColor);
	}

	// Helper function for flipping pixels along a vertical axis
	private void flipPixel2(int x, int y, Picture original, int width) {
		Pixel origPixel = original.getPixel(x, y);
		Color origColor = origPixel.getColor();
		Pixel newPixel = this.getPixel(width - x - 1, y);
		newPixel.setColor(origColor);
	}

	// Helper function for flipping pixels along a forward diagonal axis
	private void flipPixel3(int x, int y, Picture original, int width,
			int height) {
		Pixel origPixel = original.getPixel(x, y);
		Color origColor = origPixel.getColor();
		Pixel newPixel = this.getPixel(height - y - 1, width - x - 1);
		newPixel.setColor(origColor);
	}

	// Helper function for flipping pixels along a backward diagonal axis
	private void flipPixel4(int x, int y, Picture original, int width,
			int height) {
		Pixel origPixel = original.getPixel(x, y);
		Color origColor = origPixel.getColor();
		Pixel newPixel = this.getPixel(y, x);
		newPixel.setColor(origColor);
	}
	
	/**
	 * Test case for the helper function flipPixel(). Ensures that when a half black half 
	 * white image is flipped about certain axis such that a white pixel must turn black, 
	 * the proper pixel is turned black
	 */
	private static boolean flipPixelWorks() {
		/* Creates a new 10 by 10 test image, upper half black and lower half white
		 *   __________
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |          |
		 *  |          |
		 *  |          |
		 *  |          |
		 *  |__________|
		 */
		Picture test = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 6; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		// Horizontal axis test
		Picture test2 = new Picture(test);
		test2.flipPixel1(7, 2, test, 10);
		boolean rotate1 = (test2.getPixel(7, 7).colorDistance(Color.BLACK) == 0);
		// Vertical axis test
		// Vertical test image
		Picture test3 = new Picture(test.rotate(1));
		test3.flipPixel2(2,  2, test, 10);
		boolean rotate2 = (test3.getPixel(7, 2).colorDistance(Color.BLACK) == 0);
		// Forward slash test
		Picture test4 = new Picture(test);
		test4.flipPixel3(2, 2, test, 10, 10);
		boolean rotate3 = (test4.getPixel(7, 7).colorDistance(Color.BLACK) == 0);
		// Backwards slash test
		Picture test5 = new Picture(test);
		test5.flipPixel4(7, 2, test, 10, 10);
		boolean rotate4 = (test5.getPixel(2, 7).colorDistance(Color.BLACK) == 0);
		return rotate1 && rotate2 && rotate3 && rotate4;
	}

	/**
	 * @param threshold
	 *            Threshold to use to determine the presence of edges.
	 * 
	 * @return A new Picture that contains only the edges of this Picture. For
	 *         each pixel, we separately consider the color distance between
	 *         that pixel and the one pixel to its left, and also the color
	 *         distance between that pixel and the one pixel to the north, where
	 *         applicable. As an example, we would compare the pixel at (3, 4)
	 *         with the pixels at (3, 3) and the pixels at (2, 4). Also, since
	 *         the pixel at (0, 4) only has a pixel to its north, we would only
	 *         compare it to that pixel. If either of the color distances is
	 *         larger than the provided color threshold, it is set to black
	 *         (with an alpha of 255); otherwise, the pixel is set to white
	 *         (with an alpha of 255). The pixel at (0, 0) will always be set to
	 *         white.
	 * @throws IllegalArgumentException 
	 */
	public Picture showEdges(int threshold) throws IllegalArgumentException {
		/* REPLACE THE CODE BELOW WITH YOUR OWN. */
		if(threshold < 0){
			throw new IllegalArgumentException("Your choice of a negative threshold is nonsensical... try again");
		}
		Picture newPicture = new Picture(this);
		int width = this.getWidth();
		int height = this.getHeight();
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (x == 0 && y == 0) {
					newPicture.edgePixelLeftUp(x, y);
				} else if (x == 0) {
					newPicture.edgePixelLeft(x, y, threshold, this);
				} else if (y == 0) {
					newPicture.edgePixelUp(x, y, threshold, this);
				} else {
					newPicture.edgePixel(x, y, threshold, this);
				}
			}
		}
		return newPicture;
	}

	// Helper function for showEdges() which checks pixels with their neighbors
	// and turns them black or white
	private void edgePixel(int x, int y, int threshold, Picture original) {
		Pixel newPixel = this.getPixel(x, y);
		Pixel origPixel = original.getPixel(x, y);
		Pixel leftPixel = original.getPixel(x - 1, y);
		Pixel upPixel = original.getPixel(x, y - 1);
		Color leftColor = leftPixel.getColor();
		Color upColor = upPixel.getColor();
		int leftDistance = ((int) origPixel.colorDistance(leftColor));
		int upDistance = ((int) origPixel.colorDistance(upColor));
		if (leftDistance > threshold || upDistance > threshold) {
			newPixel.setColor(Color.black);
			newPixel.setAlpha(255);
		} else {
			newPixel.setColor(Color.white);
			newPixel.setAlpha(255);
		}
	}

	// Helper function for showEdges() similar to edgePixel but does not check
	// upper pixel
	private void edgePixelUp(int x, int y, int threshold, Picture original) {
		Pixel newPixel = this.getPixel(x, y);
		Pixel origPixel = original.getPixel(x, y);
		Pixel leftPixel = original.getPixel(x - 1, y);
		Color leftColor = leftPixel.getColor();
		int leftDistance = ((int) origPixel.colorDistance(leftColor));
		if (leftDistance > threshold) {
			newPixel.setColor(Color.black);
			newPixel.setAlpha(255);
		} else {
			newPixel.setColor(Color.white);
			newPixel.setAlpha(255);
		}
	}

	// Helper function for showEdges() similar to edgePixel but does not check
	// left pixel
	private void edgePixelLeft(int x, int y, int threshold, Picture original) {
		Pixel newPixel = this.getPixel(x, y);
		Pixel origPixel = original.getPixel(x, y);
		Pixel upPixel = original.getPixel(x, y - 1);
		Color upColor = upPixel.getColor();
		int upDistance = ((int) origPixel.colorDistance(upColor));
		if (upDistance > threshold) {
			newPixel.setColor(Color.black);
			newPixel.setAlpha(255);
		} else {
			newPixel.setColor(Color.white);
			newPixel.setAlpha(255);
		}
	}

	// Helper function for showEdges(); special case for upper left pixel
	private void edgePixelLeftUp(int x, int y) {
		Pixel newPixel = this.getPixel(x, y);
		newPixel.setColor(Color.white);
		newPixel.setAlpha(255);
	}
	
	/**
	 * Test case for the helper function edgePixel(). Ensures that when a half black half 
	 * white image is asked to detect its edges, the proper pixels turn black
	 */
	private static boolean edgePixelWorks() {
		/* Creates a new 10 by 10 test image, upper half black and lower half white
		 *   __________
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |**********|
		 *  |          |
		 *  |          |
		 *  |          |
		 *  |          |
		 *  |__________|
		 */
		Picture test = new Picture(10, 10);
		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 6; j++){
				test.getPixel(i,  j).setColor(Color.BLACK);
			}
		}
		// Normal
		Picture test1 = new Picture(10, 10);
		test1.edgePixel(2, 6, 10, test);
		boolean case1 = (test1.getPixel(2, 6).colorDistance(Color.BLACK) == 0);
		// Upper Boundary
		// Vertical test image
		Picture test2 = new Picture(10, 10);
		test2.edgePixelUp(6,  0, 10, test.rotate(-1));
		boolean case2 = (test2.getPixel(6, 0).colorDistance(Color.BLACK) == 0);
		// Left Boundary
		Picture test3 = new Picture(10, 10);
		test3.edgePixelLeft(0, 6, 10, test);
		boolean case3 = (test3.getPixel(0, 6).colorDistance(Color.BLACK) == 0);
		// Upper Left Corner
		Picture test4 = new Picture(10, 10);
		test4.edgePixelLeftUp(0, 0);
		boolean case4 = (test4.getPixel(0, 0).colorDistance(Color.WHITE) == 0);
		return case1 && case2 && case3 && case4;
	}
	
	

	// ////////////////////////////// Level 3 //////////////////////////////////

	/**
	 * @return A new Picture that is the ASCII art version of this Picture. To
	 *         implement this, the Picture is first converted into its grayscale
	 *         equivalent. Then, starting from the top left, the average color
	 *         of every chunk of 10 pixels wide by 20 pixels tall is computed.
	 *         Based on the average value obtained, this chunk will be replaced
	 *         by the corresponding ASCII character specified by the table
	 *         below.
	 * 
	 *         The ASCII characters to be used are available as Picture objects,
	 *         also of size 10 pixels by 20 pixels. The following characters
	 *         should be used, depending on the average value obtained:
	 * 
	 *         0 to 18: # (Picture.BMP_POUND) 19 to 37: @ (Picture.BMP_AT) 38 to 
	 *         56: & (Picture.BMP_AMPERSAND) 57 to 75: $ (Picture.BMP_DOLLAR) 76
	 *         to 94: % (Picture.BMP_PERCENT) 95 to 113: | (Picture.BMP_BAR) 114
	 *         to 132: ! (Picture.BMP_EXCLAMATION) 133 to 151: ;
	 *         (Picture.BMP_SEMICOLON) 152 to 170: : (Picture.BMP_COLON) 171 to
	 *         189: ' (Picture.BMP_APOSTROPHE) 190 to 208: ` (Picture.BMP_GRAVE)
	 *         209 to 227: . (Picture.BMP_DOT) 228 to 255: (Picture.BMP_SPACE)
	 * 
	 *         We provide a getAsciiPic method to obtain the Picture object
	 *         corresponding to a character, given any of the static Strings
	 *         mentioned above.
	 * 
	 *         Note that the resultant Picture should be the exact same size as
	 *         the original Picture; this might involve characters being
	 *         partially copied to the final Picture.
	 */
	public Picture convertToAscii() {
		/* REPLACE THE CODE BELOW WITH YOUR OWN. */
		Picture grayPicture = this.grayscale();
		Picture newPicture = new Picture(grayPicture);
		int width = this.getWidth();
		int height = this.getHeight();
		for (int x = 4; x < width; x = x + 10) {
			for (int y = 9; y < height; y = y + 20) {
				newPicture.asciiPixel(x, y, width, height);
			}
		}
		return newPicture;
	}

	// Helper function for converToAscii() that converts pixel groups to the
	// correct ascii image (a lot of duplicate code)
	public void asciiPixel(int x, int y, int width, int height) {
		// leftBound, rightBound, upBound, and downBound represent boundaries so
		// that all pixels searched fall within the picture
		int leftBound = x - 4;
		int rightBound = x + 5;
		int upBound = y - 9;
		int downBound = y + 10;
		if (x >= width - 5 - 1)
			rightBound = width - 1;
		if (y >= height - 10 - 1)
			downBound = height - 1;
		int average = 0;
		for (int i = leftBound; i <= rightBound; i++) {
			for (int j = upBound; j <= downBound; j++) {
				Pixel currentPixel = this.getPixel(i, j);
				average += currentPixel.getAverage();
			}
		}
		int numPixels = (rightBound - leftBound + 1)
				* (downBound - upBound + 1);
		average = average / numPixels;
		Picture asciiPicture = getAsciiPic(average);
		int i2 = 0;
		int j2;
		for (int k = leftBound; k <= rightBound; k++) {
			j2 = 0;
			for (int z = upBound; z <= downBound; z++) {
				Pixel asciiPixel = asciiPicture.getPixel(i2, j2);
				Color asciiColor = asciiPixel.getColor();
				Pixel currentPixel = this.getPixel(k, z);
				currentPixel.setColor(asciiColor);
				j2++;
			}
			i2++;
		}

	}
	
	/**
	 * Test case for the helper function asciiPixel(). Ensures that a each
	 * "picture block" returns the proper ascii block (tests all possible 
	 * blocks as averages move in groups of 20). Does this by creating a test 
	 * image the is purely an average color and tests if asciiPixel creates 
	 * the proper ascii image
	 */
	private static boolean asciiPixelWorks() {
		int average = 6;
		Picture test = new Picture(10, 20);
		while(average < 255){
			for(int i = 0; i < 10; i++){
				for(int j = 0; j < 20; j++){
					test.getPixel(i, j).setRed(average);
					test.getPixel(i, j).setGreen(average);
					test.getPixel(i, j).setBlue(average);
				}
			}
			test.asciiPixel(4, 9, 10, 20);
			if(!test.equals(getAsciiPic(average)))
				return false;
			average += 20;
		}
		return true;
	}

	/**
	 * Blurs this Picture. To achieve this, the algorithm takes a pixel, and
	 * sets it to the average value of all the pixels in a square of side (2 *
	 * blurThreshold) + 1, centered at that pixel. For example, if blurThreshold
	 * is 2, and the current pixel is at location (8, 10), then we will consider
	 * the pixels in a 5 by 5 square that has corners at pixels (6, 8), (10, 8),
	 * (6, 12), and (10, 12). If there are not enough pixels available -- if the
	 * pixel is at the edge, for example, or if the threshold is larger than the
	 * image -- then the missing pixels are ignored, and the average is taken
	 * only of the pixels available.
	 * 
	 * The red, blue, green and alpha values should each be averaged separately.
	 * 
	 * @param blurThreshold
	 *            Size of the blurring square around the pixel.
	 * 
	 * @return A new Picture that is the blurred version of this Picture, using
	 *         a blurring square of size (2 * threshold) + 1.
	 * @throws IllegalArgumentException 
	 */
	public Picture blur(int blurThreshold) throws IllegalArgumentException {
		/* REPLACE THE CODE BELOW WITH YOUR OWN. */
		if(blurThreshold < 0){
			throw new IllegalArgumentException("Your choice of a negative threshold is nonsensical... try again");
		}
		Picture newPicture = new Picture(this);
		int width = this.getWidth();
		int height = this.getHeight();
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				newPicture.blurPixel(x, y, height, width, this, blurThreshold);
			}
		}
		return newPicture;
	}

	// Helper function for blue() which blurs a pixel
	private void blurPixel(int x, int y, int height, int width,
			Picture original, int threshold) {
		// leftBound, rightBound, upBound, and downBound represent boundaries so
		// that all pixels searched fall within the picture
		int leftBound = x - threshold;
		int rightBound = x + threshold;
		int upBound = y - threshold;
		int downBound = y + threshold;
		if (x < threshold)
			leftBound = 0;
		if (y < threshold)
			upBound = 0;
		if (width - x - 1 < threshold)
			rightBound = width - 1;
		if (height - y - 1 < threshold)
			downBound = height - 1;
		int redAverage = 0;
		int greenAverage = 0;
		int blueAverage = 0;
		int alphaAverage = 0;
		for (int i = leftBound; i <= rightBound; i++) {
			for (int j = upBound; j <= downBound; j++) {
				Pixel currPixel = original.getPixel(i, j);
				redAverage += currPixel.getRed();
				greenAverage += currPixel.getGreen();
				blueAverage += currPixel.getBlue();
				alphaAverage += currPixel.getAlpha();
			}
		}
		int numPixels = ((rightBound - leftBound + 1) * (downBound - upBound + 1));
		redAverage = redAverage / numPixels;
		greenAverage = greenAverage / numPixels;
		blueAverage = blueAverage / numPixels;
		alphaAverage = alphaAverage / numPixels;
		Pixel newPixel = this.getPixel(x, y);
		newPixel.setRed(redAverage);
		newPixel.setGreen(greenAverage);
		newPixel.setBlue(blueAverage);
		newPixel.setAlpha(alphaAverage);
	}
	
	/**
	 * Test case for the helper function blurPixel(). Creates a test image and blurs 
	 * it with threshold being the size of the image. Checks if the colors are 
	 * the proper averages. In this case there are 9 pixel with a total Red of 90, total 
	 * Green of 36, and total Blue of 9, translating into an average Red of 10, 
	 * Green of 4, and Blue of 1
	 */
	private static boolean blurPixelWorks() {
		Picture test = new Picture(3, 3);
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				test.getPixel(i, j).setRed(0);
				test.getPixel(i, j).setGreen(0);
				test.getPixel(i, j).setBlue(0);
			}
		}
		test.getPixel(1, 2).setRed(90);
		test.getPixel(2, 2).setGreen(36);
		test.getPixel(0, 0).setBlue(9);
		test.blurPixel(1, 1, 3, 3, test, 1);
		Pixel ref = test.getPixel(1, 1);
		if(ref.getRed() != 10 || ref.getGreen() != 4 || ref.getBlue() != 1)
			return false;
		return true;
	}

	/**
	 * @param x
	 *            x-coordinate of the pixel currently selected.
	 * @param y
	 *            y-coordinate of the pixel currently selected.
	 * @param threshold
	 *            Threshold within which to delete pixels.
	 * @param newColor
	 *            New color to color pixels.
	 * 
	 * @return A new Picture where all the pixels connected to the currently
	 *         selected pixel, and which differ from the selected pixel within
	 *         the provided threshold (in terms of color distance), are colored
	 *         with the new color provided.
	 */
	public Picture paintBucket(int x, int y, int threshold, Color newColor) {
		/* REPLACE THE CODE BELOW WITH YOUR OWN. */
		if (!inRange(x, y)) {
			throw new IllegalArgumentException("pixel out of range");
		}
		if (threshold < 0 || threshold > 100) {
			throw new IllegalArgumentException(
					"bad threshold(1-100): " + threshold);
		}
		if (newColor == null) {
			throw new IllegalArgumentException("new color not given");
		}
		Picture newPic = new Picture(this);
		Color original = this.getPixel(x, y).getColor();

		boolean visited[][] = new boolean[this.getWidth()][this.getHeight()];
		LinkedList<Point> toProcess = new LinkedList<Point>();
		toProcess.add(new Point(x, y));
		while (!toProcess.isEmpty()) {
			Point p = toProcess.pop();
			x = p.x;
			y = p.y;

			// calculate adjacent pixels
			int[][] toVisit = { { x - 1, y - 1 }, { x - 1, y },
					{ x - 1, y + 1 }, { x, y - 1 }, { x, y + 1 },
					{ x + 1, y - 1 }, { x + 1, y }, { x + 1, y + 1 } };

			for (int i = 0; i < toVisit.length; i++) {
				// coordinates of adjacent pixel
				int adjX = toVisit[i][0], adjY = toVisit[i][1];

				if (inRange(adjX, adjY)
						&& this.getPixel(adjX, adjY).colorDistance(original) <= threshold
						&& !visited[adjX][adjY]) {
					visited[adjX][adjY] = true;
					toProcess.add(new Point(adjX, adjY));
				}
			}

			Pixel px = newPic.getPixel(x, y);
			px.setColor(newColor);
		}

		return newPic;
	}

	/**
	 * @param x
	 *            x-coordinate of the pixel to check.
	 * @param y
	 *            y-coordinate of the pixel to check.
	 * 
	 * @return true if the given pixel is within the borders, otherwise false
	 */
	private boolean inRange(int x, int y) {
		return 0 <= x && x < this.getWidth() && 0 <= y && y < this.getHeight();
	}

	// /////////////////////// PROJECT 1 ENDS HERE /////////////////////////////

	public boolean equals(Object obj) {
		if (!(obj instanceof Picture)) {
			return false;
		}

		Picture p = (Picture) obj;
		// Check that the two pictures have the same dimensions.
		if ((p.getWidth() != this.getWidth())
				|| (p.getHeight() != this.getHeight())) {
			return false;
		}

		// Check each pixel.
		for (int x = 0; x < this.getWidth(); x++) {
			for (int y = 0; y < this.getHeight(); y++) {
				if (!this.getPixel(x, y).equals(p.getPixel(x, y))) {
					return false;
				}
			}
		}

		return true;
	}

	/**
	 * Helper method for loading a picture in the current directory.
	 */
	protected static Picture loadPicture(String pictureName) {
		URL url = Picture.class.getResource(pictureName);
		return new Picture(url.getFile().replaceAll("%20", " "));
	}

	/**
	 * Helper method for loading the pictures corresponding to each character
	 * for the ASCII art conversion.
	 */
	private static Picture getAsciiPic(int grayValue) {
		int asciiIndex = (int) grayValue / 19;

		if (BMP_AMPERSAND == null) {
			BMP_AMPERSAND = Picture.loadPicture("ampersand.bmp");
			BMP_APOSTROPHE = Picture.loadPicture("apostrophe.bmp");
			BMP_AT = Picture.loadPicture("at.bmp");
			BMP_BAR = Picture.loadPicture("bar.bmp");
			BMP_COLON = Picture.loadPicture("colon.bmp");
			BMP_DOLLAR = Picture.loadPicture("dollar.bmp");
			BMP_DOT = Picture.loadPicture("dot.bmp");
			BMP_EXCLAMATION = Picture.loadPicture("exclamation.bmp");
			BMP_GRAVE = Picture.loadPicture("grave.bmp");
			BMP_HASH = Picture.loadPicture("hash.bmp");
			BMP_PERCENT = Picture.loadPicture("percent.bmp");
			BMP_SEMICOLON = Picture.loadPicture("semicolon.bmp");
			BMP_SPACE = Picture.loadPicture("space.bmp");
		}

		switch (asciiIndex) {
		case 0:
			return Picture.BMP_HASH;
		case 1:
			return Picture.BMP_AT;
		case 2:
			return Picture.BMP_AMPERSAND;
		case 3:
			return Picture.BMP_DOLLAR;
		case 4:
			return Picture.BMP_PERCENT;
		case 5:
			return Picture.BMP_BAR;
		case 6:
			return Picture.BMP_EXCLAMATION;
		case 7:
			return Picture.BMP_SEMICOLON;
		case 8:
			return Picture.BMP_COLON;
		case 9:
			return Picture.BMP_APOSTROPHE;
		case 10:
			return Picture.BMP_GRAVE;
		case 11:
			return Picture.BMP_DOT;
		default:
			return Picture.BMP_SPACE;
		}
	}

	public static void main(String[] args) {
		Picture initialPicture = new Picture(
				FileChooser.pickAFile(FileChooser.OPEN));
		initialPicture.explore();
	}

} // End of Picture class
