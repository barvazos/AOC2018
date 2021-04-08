#include "aoc2018_util.h"

using Prerequisites = std::map<char, std::set<char>>;
using PQueue = std::priority_queue<char, std::vector<char>, std::greater<>>;

Prerequisites read_prerequisites(const std::string& input)
{
    std::ifstream ifs(input);
    Prerequisites prerequisites;
    std::string s;

    while(std::getline(ifs, s))
    {
        char letter;
        char pre_letter;
        std::sscanf(s.c_str(), "Step %c must be finished before step %c can begin.", &pre_letter, &letter);
        prerequisites[letter].insert(pre_letter);
        if (prerequisites.find(pre_letter) == prerequisites.end())
        {
            prerequisites[pre_letter] = {};
        }
    }
    return prerequisites;
}

bool are_preqs_done(const std::set<char>& preqs, const std::string& done)
{
    for (char letter: preqs)
    {
        if (done.find(letter) != std::string::npos)
        {
            return false;
        }
    }
    return true;
}

void update_available_jobs(Prerequisites& prerequisites, PQueue& available_jobs, char job_done, std::set<char>& scheduled_jobs)
{
    for (auto& [letter, preqs] : prerequisites)
    {
        if (preqs.find(job_done) != preqs.end())
        {
            preqs.erase(preqs.find(job_done));
        }

        if (scheduled_jobs.find(letter) == scheduled_jobs.end() && preqs.empty())
        {
            available_jobs.push(letter);
            scheduled_jobs.insert(letter);
        }
    }
}

std::string solve_part_1(Prerequisites& prerequisites)
{
    PQueue available_jobs;
    std::set<char> scheduled;

    for (auto& [letter, preqs] : prerequisites)
    {        
        if (preqs.empty())
        {
            available_jobs.push(letter);
            scheduled.insert(letter);
        }
    }

    std::string jobs_done = "";

    while(!available_jobs.empty())
    {
        char cur_job = available_jobs.top();
        available_jobs.pop();
        prerequisites.erase(cur_job);
        
        jobs_done += cur_job;
        update_available_jobs(prerequisites, available_jobs, cur_job, scheduled);
    }
    return jobs_done;
}

// int32_t solve_part_2()
// {

// }

int32_t main(int32_t argc, char *argv[])
{
	if (argc < 2) {
        std::cerr << "Missing an input file\n";
        return -1;
    }

    Prerequisites prerequisites = read_prerequisites(argv[1]);
	std::cout << "Day07 part 1 solution is: " << solve_part_1(prerequisites) << std::endl;
	// std::cout << "Day07 part 2 solution is: " << solve_part_2() << std::endl;
}