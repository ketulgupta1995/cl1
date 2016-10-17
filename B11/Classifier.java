package b11;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;

import weka.classifiers.Evaluation;
import weka.classifiers.bayes.NaiveBayes;
import weka.core.Instances;

public class Classifier {
	public static BufferedReader readDataFile(String filename) {
		BufferedReader inputReader = null;
 
		try {
			inputReader = new BufferedReader(new FileReader(filename));
		} catch (FileNotFoundException ex) {
			System.err.println("File not found: " + filename);
		}
 
		return inputReader;
	}
	public static void main(String[] args) {
		BufferedReader read;
		try {
			//read = readDataFile("src/train.arff");
			
			//System.out.println(read.readLine());
			//Instances train = new Instances(read);
			//train.setClassIndex(train.numAttributes()-1);
			//read.close();
			
			read = new BufferedReader (new FileReader("test.arff")); 
            Instances train = new Instances(read); 
            train.setClassIndex(train.numAttributes()-1);
			
			NaiveBayes nB = new NaiveBayes();
			nB.buildClassifier(train);
			Evaluation eval = new Evaluation(train);
			eval.crossValidateModel(nB, train, 10, new Random(1));
			System.out.println("Naive Bayes Classification\n");
			System.out.println(eval.toSummaryString("\nResults===============>\n",true));
			//System.out.println(eval.fMeasure(1)+" "+eval.precision(1)+" "+eval.recall(1));
			System.out.println(eval.toMatrixString("\nConfusion Matrix: false positives and false negatives\n======\n"));
		System.out.println(eval.toClassDetailsString("Class Details..\n"));
		//System.out.println(eval.truePositiveRate(1));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
		
	}
}
