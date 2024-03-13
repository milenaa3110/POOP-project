package project;

import java.awt.Graphics;
import java.awt.LayoutManager;
import java.util.HashMap;

import javax.swing.JPanel;


public class Scene extends JPanel {

	
	private Chart chartObj;
	
	public Scene() {
	}
	
	void addObject(int chart, HashMap<String, String> data, int x, int y, int height, int weight ) {
		if (chart == 0) {
			chartObj = new PieChart(x, y, height, weight, data );
			repaint();
		}
		else {
			chartObj = new XYchart(x, y, height, weight, data );
			repaint();
		}
		
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		if (chartObj instanceof PieChart) {
			PieChart pc = (PieChart) chartObj;
			pc.paint(g);
		}
		else {
			XYchart xyC = (XYchart) chartObj;
			xyC.paint(g);
		}
	}

}
