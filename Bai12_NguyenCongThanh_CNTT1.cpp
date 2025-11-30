#include <iostream>
#include <string>
#include <fstream>
#include "stack_template.h"
#include "vector_template.h"

using namespace std;

class DoThi{
private:
	int n; // so dinh trong do thi
	Vector<string> tenDinh;
	Vector<Vector <int> > a; // ma tran ke
public:
	void NhapDoTHi(const string &filename){
		ifstream fin(filename);
		if (!fin){
			cout << "Loi mo file" << endl;
			return;
		} 
		fin >> n;
		tenDinh.resize(n);
		for(int i = 0; i < n; i++){
			fin >> tenDinh[i];
		}
		
		a.resize(n);
		for(int i = 0; i < n; i++){
			a[i].resize(n);
		}
		for (int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				fin >> a[i][j];
			}
		}
		
		fin.close();
	}
	
	void GhiDoThiRaFileMoi(const string &filename){
		ofstream fout(filename);
		for(int i = 0 ; i < n ; i++){
			fout << "\t" << tenDinh[i];
		}
		fout << "\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++){
				fout  << " "<< a[i][j];
			} 
            fout << "\n";
        }
        fout.close();
	}
	
	void DFS(int start, int end, const string &filename){
		ofstream fout (filename, ios::app);
		Vector<bool> visited(n, false);
		stack<int> st;
		Vector<int> parent(n, -1); // dung de duyet nguoc lai, tim duong di tu start den end
		
		st.push(start);
		visited[start] = true;
		
		while(!st.empty()){
			int u = st.top();
			st.pop();
			
			if(u == end) break;
			for(int v = n - 1; v >= 0; v --){ // duyet visited
				if(a[u][v] != 0 && !visited[v]){ // neu co duong di ti diem dang xet den, va chua di qua thi them vao stack
					visited[v] = true;
					parent[v] = u;
					st.push(v);
				}
			}
		}
		if(!visited[end]){
			cout << "khong co duong di"<< endl;
			fout << "khong co duong di"<< "\n";
		}
		else{
			cout << "Duong di: ";
			for(int v = end; v != -1; v = parent[v]){
				cout << tenDinh[v] << " ";
			}
			cout << "\n";
			// in vao file
			fout << "Duong di: ";
			for(int v = end; v != -1; v = parent[v]){
				fout << tenDinh[v] << " ";
			}
			fout << "\n";
		}
		fout.close();
	}
	
	Vector<string> getTenDinh(){
		return tenDinh;
	}
};

int main(){
	DoThi dt;
	dt.NhapDoTHi("DoThi.txt");
	dt.GhiDoThiRaFileMoi("DoThi_KetQua.txt");
	Vector<string> temp = dt.getTenDinh();
	
	cout << "Do thi gom cac dinh: ";
	for(int i = 0 ; i < temp.Size(); i++){
		cout << "\t" << temp[i];
	}
	cout << "\n";
	cout << "Chon dinh dau va cuoi:"<< endl;
	string s, e;
	int a, b;
	cout << "Diem dau:"; cin >> s; cout <<"\n";
	cout << "Diem cuoi:"; cin >> e; cout <<"\n";

	a = temp.find(s) - temp.begin();
	b = temp.find(e) - temp.begin();
	
	dt.DFS(a, b, "DoThi_KetQua.txt");
}
