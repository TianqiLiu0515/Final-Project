#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <deque>
#include <stack>
#include <map>
using namespace std;

vector<int> readag(string filename){
    string str;
    ifstream fin;
    fin.open(filename);
    string seeds = "seeds: ";
    string grad = "grad_iterations: ";
    vector<int> argu;
    int seedN;
    int iterationN;
    while (!fin.eof())
    {
        getline(fin, str);
        size_t f1 = str.find(seeds);
        size_t f2 = str.find(grad);
        if (f1 != str.npos)
        {
            str.replace(str.find(seeds), seeds.length(), "");
            seedN = std::atoi(str.c_str());
            argu.push_back(seedN);
        }
        if (f2 != str.npos)
        {
            str.replace(str.find(grad), grad.length(), "");
            iterationN = std::atoi(str.c_str()) + 1;
            argu.push_back(iterationN);
            break;
        }
    }
    return argu;
}

double** readdata(string filename, vector<int> argu){
    string str;
    ifstream fin;
    fin.open(filename);
//    string seeds = "seeds: ";
//    string grad = "grad_iterations: ";
//    int seedN;
//    int iterationN;
//    while (!fin.eof())
//    {
//        getline(fin, str);
//        size_t f1 = str.find(seeds);
//        size_t f2 = str.find(grad);
//        if (f1 != str.npos)
//        {
//            str.replace(str.find(seeds), seeds.length(), "");
//            seedN = std::atoi(str.c_str());
//        }
//        if (f2 != str.npos)
//        {
//            str.replace(str.find(grad), grad.length(), "");
//            iterationN = std::atoi(str.c_str()) + 1;
//            break;
//        }
//    }
    double **gradV = new double*[argu[0]];
    for (int i =0; i<argu[0]; i++)
    {
        gradV[i] = new double[argu[1]];
    }

    for (int i = 0; i < argu[0]; i++)
    {
        for(int j = 0; j < argu[1]; j++)
        {
            gradV[i][j] = 0;
        }
    }

    string ori = "Original_grad: ";
    string cha = "Changed_grad: ";
    int m = 0;
    int n = 0;
    double tempvalue;
    while (!fin.eof())
    {
        getline(fin, str);
        size_t fo = str.find(ori);
        size_t fc = str.find(cha);
        if (fo != str.npos)
        {
            str.replace(str.find(ori), ori.length(), "");
            tempvalue = std::atof(str.c_str());

            gradV[n][0] = tempvalue;
            n++;
            m = 1;
        }
        if (fc != str.npos)
        {
            str.replace(str.find(cha), cha.length(), "");
            tempvalue = std::atof(str.c_str());
            gradV [n - 1][m] = tempvalue;
            m++;
        }
    }
    cout<<"GradV: "<<endl;
    for (int i = 0; i < argu[0]; i++)
    {
        cout<<endl;
        for(int j = 0; j < argu[1]; j++)
        {
//            if(gradV[i][j] != 0){
//                cout<<gradV[i][j]<<" ";
//            }
            cout<<gradV[i][j]<<" ";
        }
    }
    return gradV;
}

deque<int> mins(double **grad, vector<int> argu){
    int n = 0;
    int m = 0;
    double **changeV = new double*[argu[0]];
    deque<int> count;
    for (int i =0; i<argu[0]; i++)
    {
        changeV[i] = new double[argu[1]];
    }

    for (int i = 0; i < argu[0]; i++)
    {
        for(int j = 0; j <= argu[1]; j++)
        {
            changeV[i][j] = 0;
        }
    }

    while(grad[n][0] != 0)
    {
        m = 1;
        while(grad[n][m] != 0 && m != argu[1] && m < argu[1])
        {
            changeV[n][m] = grad[n][m] - grad[n][m - 1];
            m++;
        }
        count.push_back(m - 1);
        changeV[n][m] = m - 1;
        n++;
    }
    cout<<endl;
    cout<<"changeV: "<<endl;
    for (int i = 0; i < argu[0]; i++)
    {
        cout<<endl;
        for(int j = 0; j <= argu[1]; j++)
        {
            if (changeV[i][j] != 0 && changeV[i][j] >= 0){
                cout<<changeV[i][j]<<" ";
            }

        }
    }
    return count;
}

int Nochange(deque<int> count)
{
    int N = 0;
    for(int i = 0; i < count.size(); i++)
    {
        if (count[i] == 20)
        {
            N++;
        }
    }
    return N;
}

int Changes(deque<int> count)
{
    int C = 0;
    for (int i = 0; i < count.size(); i++)
    {
        if (count[i] < 20 && count[i] > 0)
        {
            C++;
        }
    }
    return C;
}

//map<string, vector<double>> get_result() {
//    vector<string> files;
//    files.push_back("2019.04.29-17_37_21_fisheye.txt");
//    files.push_back("2019.04.29-15_25_09_circle.txt");
//    files.push_back("2019.04.29-15_30_49_color.txt");
//    files.push_back("2019.04.29-15_39_22_blur.txt");
//    map<string, vector<double>> result;
//    for(int i = 0; i < files.size(); i++) {
//        string filename = files[i];
//        unsigned int pos1 = filename.find('_');
//        unsigned int pos2 = filename.find('.');
//        string key = filename.substr(pos1, pos2 - pos1);
//        vector<int> argu = readag(files[i]);
//        double **gradV = readdata(files[i], argu);
//        deque<int> count = mins(gradV, argu);
//        int N = Nochange(count);
//        int C = Changes(count);
//        double n = (double)N / (double)argu[0];
//        double c = (double)C / (double)argu[0];
//        cout<<endl;
//        cout<<"n: "<<n<<" c: "<<c<<endl;
//        vector<double> value;
//        value.push_back(n);
//        value.push_back(c);
//        result[key] = value;
//    }
//    return result;
//}


int main()
{
    vector<string> files;
    files.push_back("2019.04.29-17_37_21_fisheye.txt");
    files.push_back("2019.04.29-15_25_09_circle.txt");
    files.push_back("2019.04.29-15_30_49_color.txt");
    files.push_back("2019.04.29-15_39_22_blur.txt");
    map<string, vector<double>> result;
    vector<vector<double>> v(files.size());

    for(int i = 0; i < files.size(); i++) {
        string filename = files[i];
        unsigned int pos1 = filename.rfind('_');
        unsigned int pos2 = filename.rfind('.');
        string key = filename.substr(pos1 + 1, pos2 - pos1 - 1);
        vector<int> argu = readag(files[i]);
        double **gradV = readdata(files[i], argu);
        deque<int> count = mins(gradV, argu);
        int N = Nochange(count);
        int C = Changes(count);
        double n = (double) N / (double) argu[0];
        double c = (double) C / (double) argu[0];
        v[i].push_back(n);
        v[i].push_back(c);
        result.insert(pair<string, vector<double>> (key, v[i]));
    }
    vector<double> v1 = result["circle"];
    cout <<"circle: "<< v1[0] << " " << v1[1] << endl;
//    cout << vec1[0] << " " << vec1[1] << endl;
    vector<double> vec2 = result["color"];
    cout <<"color: "<<vec2[0] << " " << vec2[1] << endl;
    vector<double> vec3 = result["fisheye"];
    cout <<"fisheye: "<< vec3[0] << " " << vec3[1] << endl;
    vector<double> vec4 = result["blur"];
    cout <<"blur: "<<vec4[0] << " " << vec4[1] << endl;
}