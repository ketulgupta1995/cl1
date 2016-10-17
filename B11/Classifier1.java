package b11;
import java.awt.BorderLayout;
import java.io.BufferedReader;
import java.io.FileReader;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import weka.classifiers.Evaluation;
import weka.classifiers.trees.J48;
import weka.core.Instances;
import weka.gui.treevisualizer.PlaceNode2;
import weka.gui.treevisualizer.TreeVisualizer;

public class Classifier1 { 

	private static final Logger logger = LoggerFactory.getLogger(Classifier1.class);
	
    public static void main (String[] args) throws Exception 
    { 
            BufferedReader breader = null;
            
            
            
                breader = new BufferedReader (new FileReader("test.arff")); 
                Instances train = new Instances(breader); 
                train.setClassIndex(train.numAttributes()-1); 
                
                breader = new BufferedReader (new FileReader("test.arff")); 
                Instances test = new Instances(breader); 
                test.setClassIndex(test.numAttributes()-1); 
                
                breader.close();
                
                J48 tree= new J48(); 
                tree.setOptions(null); 
                tree.buildClassifier(train); 
               // Instances labeled = new Instances (test); 
                
                         
                Evaluation eval = new Evaluation(train);
    			eval.evaluateModel(tree, test);
    			System.out.println("Decision Tree\n");
    			logger.info(eval.toSummaryString("\nSummary\n======\n", false));
    			logger.info(eval.toClassDetailsString("\nClass Details\n======\n"));
    			logger.info(eval.toMatrixString("\nConfusion Matrix: false positives and false negatives\n======\n"));
    		//	System.out.println("Fmeasure"+eval.fMeasure(1));
    			
    		//	visualize(tree);
    			
            
    } 
    public static void visualize(J48 tree) throws Exception{
		// display classifier
	     final javax.swing.JFrame jf = new javax.swing.JFrame("Tree Visualizer: J48");
	     jf.setSize(500,400);
	     jf.getContentPane().setLayout(new BorderLayout());
	     TreeVisualizer tv = new TreeVisualizer(null,(tree).graph(),new PlaceNode2());
	     jf.getContentPane().add(tv, BorderLayout.CENTER);
	     jf.addWindowListener(new java.awt.event.WindowAdapter() {
	       public void windowClosing(java.awt.event.WindowEvent e) {
	         jf.dispose();
	       }
	     });
	 
	     jf.setVisible(true);
	     tv.fitToScreen();
	}
} 
