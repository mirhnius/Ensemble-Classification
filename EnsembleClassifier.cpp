#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

using namespace std;

#define L_PLACE 0
#define W_PLACE 1
#define C_PLACE 0
#define B0_PLACE 0
#define B1_PLACE 1
#define Bias_PLACE 2
#define NUMBERofCLASSIFIERS 10
#define PERCENTAGE 100
#define PRECISION 6

struct Petal{
	double Length,Width;
	int Class;
};
struct FeatureVector{
	double Betha_0,Betha_1,Bias;
};
struct Classifier{
	vector<FeatureVector>Features;
};
typedef vector<int> Classes;
typedef vector<double> TokensLineType;
typedef vector<TokensLineType> TokensType;

string read_file_content(const string& file_path);
TokensType tokenize(const string& input_file);
vector<Petal>dataset_creation(const string& file_path);
Classifier classifier_creation(const string& file_path);
Classes all_classes(const vector<Classifier>&classifiers);
vector<Classifier>all_classifiers_creation(string file_path);
int choosed_class_by_the_classifier(Classifier classifier , double length , double width);
Classes classifiers_suggestions(const vector<Classifier>& classifiers,Classes suggested, double length , double width);
int assigned_class(const vector<Classifier>& classifiers,Classes& classes, double length , double width);
void validation(const vector<Petal>& petal,vector<Classifier>& classifiers,Classes& classes);


int main(int argc, char const *argv[]){

	string data_path = argv[1],classifier_path = argv[2];
    vector<Petal> petals = dataset_creation(data_path);
    vector<Classifier> classifiers = all_classifiers_creation(classifier_path);
    Classes classes = all_classes(classifiers);
    validation(petals,classifiers,classes);
	

}


string read_file_content(const string& file_path){
	ifstream file(file_path);
	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

TokensType tokenize(const string& input_file){
	TokensType tokens;
	string line;
	stringstream full_stream(input_file);
	getline(full_stream,line,'\n');
	while(getline(full_stream,line,'\n')){
		stringstream line_stream(line);
		string token;
		TokensLineType tokens_line;
		while(getline(line_stream,token,',')){
			tokens_line.push_back(stod(token));
		}
		tokens.push_back(tokens_line);
	}
	return tokens;
}

vector<Petal>dataset_creation(const string& file_path){
	TokensType data_tokens = tokenize(read_file_content(file_path + "/dataset" + ".csv"));
	TokensType class_tokens = tokenize(read_file_content(file_path + "/labels" + ".csv"));
	int psize = data_tokens.size();
	vector<Petal> petal(psize);

	for(unsigned i = 0;i < psize;i ++){
		petal[i].Length = data_tokens[i][L_PLACE];
		petal[i].Width = data_tokens[i][W_PLACE];
		petal[i].Class = class_tokens[i][C_PLACE];
		
	}
	return petal;
}

Classifier classifier_creation(const string& file_path){
	TokensType tokens = tokenize(read_file_content(file_path));
	Classifier classifier;
	FeatureVector feature;

	for(unsigned int i = 0;i < tokens[0].size();i ++){
		feature.Betha_0 = tokens[i][B0_PLACE];
		feature.Betha_1 = tokens[i][B1_PLACE];
		feature.Bias = tokens[i][Bias_PLACE];
		classifier.Features.push_back(feature);
	}
	return classifier;
}

vector<Classifier>all_classifiers_creation(string file_path){
	vector<Classifier> classifiers;

	for(unsigned int i = 0;i < NUMBERofCLASSIFIERS; i++){
		classifiers.push_back(classifier_creation(file_path + "/classifier_" + to_string(i) + ".csv"));
	}
	return classifiers;
}

Classes all_classes(const vector<Classifier>&classifiers){
	int number_of_classes = 0,n;
	for(unsigned int i = 0;i < classifiers.size();i ++){
		n = classifiers[i].Features.size();
		if(n > number_of_classes)
			number_of_classes = n;
	}
	Classes classes(number_of_classes,0);
	return classes;
}

int choosed_class_by_the_classifier(Classifier classifier , double length , double width){
	int class_number;
	vector<FeatureVector>features = classifier.Features;
	double score,highest = 0;
	for(unsigned int i = 0;i < features.size();i ++){
		score = features[i].Betha_0 * length + features[i].Betha_1 * width + features[i].Bias;
		if(score > highest){
			highest = score;
		    class_number = i;
		}
	}

	return class_number;
}

Classes classifiers_suggestions(const vector<Classifier>& classifiers,Classes suggested, double length , double width){
	int choosed_number;
	for(unsigned int i = 0;i < classifiers.size();i ++){
		choosed_number = choosed_class_by_the_classifier(classifiers[i],length,width);
		suggested[choosed_number] ++;	
	}
	return suggested;
}

int assigned_class(const vector<Classifier>& classifiers,Classes& classes, double length , double width){
	int class_number,csize = classes.size(),highest = 0;
	Classes suggested(csize,0);
	suggested = classifiers_suggestions(classifiers,suggested,length,width);
	for(unsigned i = 0;i < csize; i++){
		if(highest < suggested[i]){
			highest = suggested[i];
			class_number = i;
		}
		else if(highest == suggested[i]){
			if(classes[i] < classes[class_number])
				class_number = i;
		}	
	}

	return class_number;
}

void validation(const vector<Petal>& petal,vector<Classifier>& classifiers,Classes& classes){

	int psize = petal.size();
	int not_mached = psize;
	double ratio;

	for(unsigned int i = 0;i < psize; i++){
		if(petal[i].Class != assigned_class(classifiers,classes,petal[i].Length ,petal[i].Width))
			not_mached --;
	}

	ratio = static_cast<double>(not_mached) / static_cast<double>(psize);
	cout.precision(PRECISION);
	cout << "Accuracy: " << PERCENTAGE * ratio << "%" << endl;
}




 

