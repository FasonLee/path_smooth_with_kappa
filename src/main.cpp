#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "matplotlibcpp.h"
#include "tension_smoother_2.hpp"
#include "reference_path.hpp"
#include "tic_toc.h"
namespace plt = matplotlibcpp;

int main(int argc, char *argv[])
{
    std::string filepath = "../data/2638.csv";
    std::string originline, line;
    std::ifstream originfile(filepath), file(filepath);

    size_t count = 0;
    while (getline(originfile, line))
    {
        count++;
    }

    std::vector<State> original_path(count);
    std::vector<double> plot_x, plot_y;

    size_t i = 0;
    while (getline(file, line))
    {
        std::istringstream ss(line);
        std::vector<double> line_data{};
        double data;
        while (ss >> data)
        {
            line_data.emplace_back(data);
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }
        plot_x.emplace_back(line_data[0]);
        plot_y.emplace_back(line_data[1]);
        original_path[i] = {line_data[0], line_data[1], line_data[2], line_data[3]};
        i++;
    }

    State start_state = original_path.front();
    TensionSmoother2 path_optimzier(original_path, start_state);
    std::shared_ptr<ReferencePath> reference_path_;
    reference_path_ = std::make_shared<ReferencePath>();
    TicToc tictoc;
    tictoc.tic();
    if (!path_optimzier.smooth(reference_path_))
    {
        std::cout << "path optimization error" << std::endl;
    }
    std::cout << "Time: " << tictoc.toc() << std::endl;

    plt::figure();
    plt::plot(plot_x, plot_y, {{"label", "Before"}}); 
    plt::plot(path_optimzier.x_list_, path_optimzier.y_list_, {{"label", "Optimized"}});
    plt::xlabel("x");
    plt::ylabel("y");
    plt::title("trajectory");
    plt::legend();
    plt::show();
    plt::save("./Trajectory.png");

    return 0;
}