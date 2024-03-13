package project;

import java.awt.Graphics;
import java.util.HashMap;

abstract public class Chart {
	private HashMap<String, String> data;
	private int x, y, height, weight;
	
	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public int getHeight() {
		return height;
	}

	public int getWeight() {
		return weight;
	}
	
	public HashMap<String, String> getData(){
		return data;
	}

	public Chart(HashMap data, int x, int y, int height, int weight) {
		this.data=data;
		this.x = x; this.y = y; this.height = height; this.weight = weight;
	}
	
	abstract void paint(Graphics g);
	

}
