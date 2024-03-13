package project;

import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;




public class PieChart extends Chart {
	public PieChart(int x, int y, int height, int weight, HashMap<String, String> data ) {
		super(data, x, y, height, weight);
	}

	@Override
	void paint(Graphics g) {
		int startAngle = 0;
		double sum = 0.0;
		HashMap<String, Double> unsortedData = new HashMap<>();
		for (String key : getData().keySet()) {
			sum+=Double.parseDouble(getData().get(key));
			unsortedData.put(key, Double.parseDouble(getData().get(key)));
		}
		g.setFont(new Font("Arial",Font.PLAIN,9));
		FontMetrics fm = g.getFontMetrics();
		System.out.println(sum);
		for (String key : unsortedData.keySet()) {
			int arc = (int) (360 * unsortedData.get(key) / sum);
			if (arc < 10) continue;
			g.setColor(new Color((int)(Math.random() * 0x1000000)));
			g.fillArc(getX() - getWeight()/2, getY() - getHeight()/2, getWeight(), getHeight(), startAngle, arc);
		    double textWidth = fm.getStringBounds(key, g).getWidth();
		    int param = 0;
		    if (Math.cos(Math.toRadians((double)(startAngle+arc/2))) <0.1) param = -1;
		    g.setColor(Color.BLACK);
		    g.drawString(key, getX()+ (int)(Math.cos(Math.toRadians((double)(startAngle+arc/2)))*getWeight()/2 * 1.1  + param * textWidth)  , getY() - (int)(Math.sin(Math.toRadians((double)(startAngle+arc/2)))*getHeight()/2 * 1.1 ));
		    startAngle+=arc;
		}
		g.setColor(new Color((int)(Math.random() * 0x1000000)));
		g.fillArc(getX()- getWeight()/2, getY()- getHeight()/2, getWeight(), getHeight(), startAngle, 360 - startAngle);
	    double textWidth = fm.getStringBounds("Other", g).getWidth();
	    int param = 0;
	    if (Math.cos(Math.toRadians((double)(startAngle+(360-startAngle)/2)))<0.1) param = -1;
	    g.setColor(Color.BLACK);
	    g.drawString("Other", getX()+ (int)(Math.cos(Math.toRadians((double)(startAngle+(360-startAngle)/2)))*getWeight()/2 * 1.1  + param * textWidth)  , getY() - (int)(Math.sin(Math.toRadians((double)(startAngle+(360-startAngle)/2)))*getHeight()/2 * 1.1 ));
	}

}
