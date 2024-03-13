package project;

import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.util.HashMap;
import java.util.TreeSet;

public class XYchart extends Chart{

	public XYchart(int x, int y, int height, int weight, HashMap<String, String> data ) {
		super(data, x, y, height, weight);
	}

	@Override
	void paint(Graphics g) {
		g.setColor(Color.BLACK);
		g.drawRect(getX() - getWeight()/2, getY() - getHeight()/2, getWeight(), getHeight());
		HashMap<String[], Double> formedData = new HashMap<>();
		TreeSet<Integer> years = new TreeSet<>();
		TreeSet<Double> neededData = new TreeSet<>();
		for (String key : getData().keySet()) {
			formedData.put(key.split(" "), Double.parseDouble(getData().get(key)));
			years.add(Integer.parseInt(key.split(" ")[0]));
			neededData.add(Double.parseDouble(getData().get(key)));
		}
		g.setFont(new Font("Arial",Font.PLAIN,9));
		FontMetrics fm = g.getFontMetrics();
		int xFirst = (years.first()/10 -1)*10;
		int xLast = (years.last()/10 + 1)* 10;
		int xInterval = ((xLast - xFirst)/70)*10;
		int yFirst = (int) ((neededData.first()+5)/10 - 1)*10;
		int yLast = (int) ((neededData.last()+5)/10 + 1)*10;
		int yInterval = ((yLast - yFirst)/7);
		for (int i = 0; i<6 ;i++) {
			double textWidth = fm.getStringBounds(String.valueOf(xFirst + xInterval * (i+1)), g).getWidth();
			g.drawString(String.valueOf(xFirst + xInterval * (i+1)), getX() - getWeight()/2 + getWeight() * (i+1) / 7 - (int)textWidth/2  , getY() + getHeight()/2 + 15);
			g.drawLine( getX() - getWeight()/2 + getWeight() * (i + 1 ) / 7 ,getY() + getHeight()/2 - 2 , getX() - getWeight()/2 + getWeight() * (i + 1 ) / 7 ,getY() + getHeight()/2 + 2 );
			textWidth = fm.getStringBounds(String.valueOf(yFirst + yInterval * (i+1)), g).getWidth();
			g.drawString(String.valueOf(yFirst + (i+1) * yInterval), getX() - getWeight()/2 - (int)textWidth - 10 ,  getY() + getHeight()/2 - getHeight() * (i+1 ) / 7 + 5 );
			g.drawLine(getX() - getWeight()/2 - 2,  getY() + getHeight()/2 - getHeight() * (i + 1 ) / 7 , getX() - getWeight()/2 + 2, getY() + getHeight()/2 - getHeight() * (i+1 ) / 7 );
		}
		
		for (String[] key : formedData.keySet()) {
			if (key[1].equals("Summer")) g.setColor(Color.RED);
			else g.setColor(Color.BLUE);
			g.fillOval(getX() - getWeight()/2  + getWeight() * (Integer.parseInt(key[0]) - xFirst) / (xLast - xFirst) - 2,getY() + getHeight()/2 - getHeight()  * (int)(formedData.get(key)-yFirst) / (yLast - yFirst) - 2 , 4, 4);
		}
	}

}
