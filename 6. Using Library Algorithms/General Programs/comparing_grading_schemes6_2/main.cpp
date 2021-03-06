#include <iostream>
#include <vector>
#include <numeric>


using namespace std;

bool did_all_hw(const Student_info& s);
double grade_aux(const Student_info& s);
double median_ananlysis(const vector<Student_info>& students );
double average( const vector<double>& v );
double average_grade(const Student_info& s);
double average_analysis(const vector<Student_info>& students );
double optimistic_median(const Student_info& s);

int main()
{
    // students who did and didn't do all their homework
    vector<Student_info> did;
    vector<Student_info> didnt;

    // read the student records and partition them
    Student_info student;
    while(read(cin,student))
    {
        if(did_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }

    // verify that the ananlyses will show us something
    if(did.empty())
    {
        cout << "No student did all the homework" << endl;
        return 1;
    }
    if( didnt.empty() )
    {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }

    // do the analyses
    write_analysis(cout, "median", median_ananlysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_ananlysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);

    return 0;
}

// median of the nonzeror elements of s.homework or 0 if no such elements exist
double optimistic_median(const Student_info& s)
{
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0 );

    if(nonzero.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero));

}

double average_analysis(const vector<Student_info>& students )
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), average_grade);

    return median(grades);
}

double average_grade(const Student_info& s)
{
    return grade(s.midterm, s.final, average(s.homework));
}


double average( const vector<double>& v )
{
    return accumulate( v.begin(), v.end(), 0.0 ) / v.size();
}

void write_analysis(ostream& out,
                    const string& name,
                    double analysis(const vector<Student_info>&),
                    const vector<Student_info>& did,
                    const vector<Student_info>& didnt )
{
    out << name << ": median(did) = " << analysis(did) <<
           ", median(didnt) = " << analysis(didnt) << endl;
}



double median_ananlysis(const vector<Student_info>& students )
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), grade_aux);

    return median(grades);
}


double grade_aux(const Student_info& s)
{
    try
    {
        return grade(s);
    }
    catch(domain_error)
    {
        return grade(s.midterm, s.final, 0);
    }
}

bool did_all_hw(const Student_info& s)
{
    return ((find(s.homework.begin(), s.homework.end(), 0))
            == s.homework.end() );
}
