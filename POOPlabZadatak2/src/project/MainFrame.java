package project;


import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GraphicsConfiguration;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.HeadlessException;
import java.awt.Insets;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTabbedPane;

import javax.swing.JTextField;

public class MainFrame extends JFrame {
	public MainFrame() {
		setSize(600,600);  
		setLayout(null); 
		populate();
	    setVisible(true);  
	    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    setLayout(new FlowLayout());
	}
	
	private void populate() {
		JTabbedPane tp=new JTabbedPane();
		tp.setBounds(50,50,400,400);
		tp.setPreferredSize(new Dimension(400, 400));
		//Panel - load
		JPanel load = new JPanel(); 
		JRadioButton gm = new JRadioButton("group mode");    
		JRadioButton im = new JRadioButton("individual mode"); 
		load.setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = 0;  
		gbc.gridy = 0; 
		gm.setSelected(true);
		ButtonGroup bg1=new ButtonGroup();
		bg1.add(im); bg1.add(gm);
		load.add(im, gbc);
		gbc.gridx = 1;  
		gbc.gridy = 0; 
		load.add(gm, gbc);
		gbc.gridx = 0;  
	    gbc.gridy = 1;  
		JTextField text = new JTextField(4);
		text.setEditable(false);
		load.add(text, gbc);
		im.addActionListener((ae)->{
			text.setEditable(true);
		});
		gm.addActionListener((ae)->{
			text.setEditable(false);
		});
		tp.add("load", load);
		
		//Panel - filter
		JPanel filterPanel = new JPanel(); 
		filterPanel.setLayout(new GridBagLayout());
		gbc.insets= new Insets( 5, 5, 5, 5);
		gbc.gridx = 0;  
		gbc.gridy = 0; 
		JLabel sportLabel = new JLabel("Sport");
		filterPanel.add(sportLabel, gbc);
		gbc.gridx = 1;  
		gbc.gridy = 0;
		JTextField sportText = new JTextField(5);
		filterPanel.add(sportText, gbc);
		gbc.gridx = 0;  
		gbc.gridy = 1; 
		JLabel yearLabel = new JLabel("Year");
		filterPanel.add(yearLabel, gbc);
		gbc.gridx = 1;  
		gbc.gridy = 1;
		JTextField yearText = new JTextField(5);
		filterPanel.add(yearText, gbc);
		gbc.gridx = 0;  
		gbc.gridy = 2; 
		JLabel typeLabel = new JLabel("Type");
		filterPanel.add(typeLabel, gbc);
		gbc.gridx = 1;  
		gbc.gridy = 2;
		JTextField typeText = new JTextField(5);
		filterPanel.add(typeText, gbc);
		gbc.gridx = 0;  
		gbc.gridy = 3; 
		JLabel medalLabel = new JLabel("Medal");
		filterPanel.add(medalLabel, gbc);
		gbc.gridx = 1;  
		gbc.gridy = 3;
		JTextField medalText = new JTextField(5);
		filterPanel.add(medalText, gbc);
		tp.add("filter", filterPanel);
		
		//Panel metric
		JPanel metricPanel = new JPanel(); 
		metricPanel.setLayout(new GridBagLayout());
		JRadioButton numOfCompetitors = new JRadioButton("number of competitors");
		JRadioButton numOfDisciplines = new JRadioButton("number of disciplines");
		JRadioButton avgWeight = new JRadioButton("average weight");
		JRadioButton avgHeight = new JRadioButton("average height");
		ButtonGroup bg2=new ButtonGroup();
		bg2.add(numOfCompetitors); bg2.add(numOfDisciplines); bg2.add(avgWeight); bg2.add(avgHeight);
		gbc.gridx = 0;  
		gbc.gridy = 0; 
		numOfCompetitors.setSelected(true);
		metricPanel.add(numOfCompetitors, gbc);
		gbc.gridx = 0;  
		gbc.gridy = 1; 
		metricPanel.add(numOfDisciplines, gbc);
		gbc.gridx = 0;  
		gbc.gridy = 2; 
		metricPanel.add(avgWeight, gbc);
		gbc.gridx = 0;  
		gbc.gridy = 3; 
		metricPanel.add(avgHeight, gbc);
		tp.add("metric", metricPanel);
		numOfDisciplines.setEnabled(false);
		avgHeight.setEnabled(false);
		avgWeight.setEnabled(false);
		//Panel view
		JPanel viewPanel = new JPanel(); 
		viewPanel.setLayout(new GridBagLayout());
		JRadioButton pieChart = new JRadioButton("Pie Chart");
		JRadioButton xyChart = new JRadioButton("XY Chart");
		ButtonGroup bg3=new ButtonGroup();
		bg3.add(pieChart); bg3.add(xyChart);
		gbc.gridx = 0;  
		gbc.gridy = 0; 
		pieChart.setSelected(true);
		viewPanel.add(pieChart, gbc);
		gbc.gridx = 0;  
		gbc.gridy = 1; 
		viewPanel.add(xyChart, gbc);
		gbc.gridx = 0;  
		gbc.gridy = 2; 
		pieChart.addActionListener((ae)->{
			numOfCompetitors.setEnabled(true);
			numOfCompetitors.setSelected(true);
			numOfDisciplines.setEnabled(false);
			avgHeight.setEnabled(false);
			avgWeight.setEnabled(false);
		});
		xyChart.addActionListener((ae)->{
			numOfDisciplines.setEnabled(true);
			avgHeight.setEnabled(true);
			avgWeight.setEnabled(true);
			if (numOfCompetitors.isSelected()) {
				numOfDisciplines.setSelected(true);
			}
			numOfCompetitors.setEnabled(false);
		});
		tp.add("view", viewPanel);
		
		//Scene Panel
		Scene scene = new Scene();
		tp.add("scene", scene);
		
		add(tp);
		JButton start = new JButton("Start");
		add(start);
		start.addActionListener((ae)->{
			start.setEnabled(false);
			DataParser dataParser = new DataParser();
			Olympics olympics = Olympics.getInstance();
			ArrayList<ArrayList<String>> events = olympics.ucitaj(new File("C:\\Users\\Milena\\eclipse-workspace\\projekatNovi\\src\\project\\13S112POOP_PZ_2122_prilog\\events.txt"));
			ArrayList<ArrayList<String>> athletes = olympics.ucitaj(new File("C:\\Users\\Milena\\eclipse-workspace\\projekatNovi\\src\\project\\13S112POOP_PZ_2122_prilog\\athletes.txt"));
			System.out.println(1);
			
			int mode = 0; String year = "0";
			if (im.isSelected()) { 
				mode = 1;
				year = text.getText();
			}
			String filterSport = sportText.getText();
			String filterYear = yearText.getText();
			String filterType = typeText.getText();
			String filterMedal = medalText.getText();
			String metricText = "";
			if (numOfCompetitors.isSelected()) metricText = numOfCompetitors.getText();
			if (numOfDisciplines.isSelected()) metricText = numOfDisciplines.getText();
			if (avgWeight.isSelected()) metricText = avgWeight.getText();
			if (avgHeight.isSelected()) metricText = avgHeight.getText();
			int chart = 0;
			if (xyChart.isSelected()) chart = 1;
			System.out.println(2);
			HashMap<String, String> resultMap = dataParser.parseData(events, athletes, mode, year, filterSport, filterYear, filterType, filterMedal, metricText, chart);
			System.out.println(3);
			
			scene.addObject(chart, resultMap,scene.getWidth()/2 , scene.getHeight()/2 , (int) (0.6*scene.getWidth()),(int) (0.6*scene.getHeight()));
			start.setEnabled(true);
		});
	}

	public static void main(String[] args) {
		new MainFrame();
	}
}
