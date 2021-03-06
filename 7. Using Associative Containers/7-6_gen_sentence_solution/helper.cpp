
#include <helper.h>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>


using std::domain_error;
using std::istream;
using std::logic_error;
using std::map;
using std::string;
using std::vector;


typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;


// read a grammar from a given input stream
Grammar read_grammar(istream& in)
{
    Grammar ret;
    string line;

    // read the input
    while (getline(in, line))
    {
        // split the input into words
        vector<string> entry = split(line);

        if (!entry.empty())
        {
            // use the category to store the associated rule
            ret[entry[0]].push_back(Rule(entry.begin()+1, entry.end()));
        }
    }

    return ret;
}


void gen_aux(const Grammar& g,
             const string& token,
             vector<string>& sentence,
             vector<string>& tokens)
{
    if (!bracketed(token))
    {
        sentence.push_back(token);
    }
    else
    {
        // locate the rule that corresponds to token
        Grammar::const_iterator it = g.find(token);

        if (it == g.end())
            throw logic_error("empty rule");

        // fetch the set of possible rules
        const Rule_collection& c = it->second;

        // from which we select one at random
        const Rule& r = c[nrand(c.size())];

        // push rule's token onto stack of tokens
        // (in reverse order, because we're pushing and popping from the back)
        for (Rule::const_reverse_iterator i = r.rbegin(); i != r.rend(); ++i)
            tokens.push_back(*i);
    }
}


// return random integer in the range [0, n)
int nrand(int n)
{
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;

    do
    {
        r = rand() / bucket_size;

    }while (r >= n);

    return r;
}
vector<string> gen_sentence(const Grammar& g)
{
    vector<string> sentence;
    vector<string> tokens;
    tokens.push_back("<sentence>");


    while (!tokens.empty())
    {
        string token = tokens.back();
        tokens.pop_back();

        gen_aux(g, token, sentence, tokens);
    }

    return sentence;

}


bool bracketed(const string& s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size()-1] == '>';
}
