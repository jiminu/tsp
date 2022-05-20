from matplotlib import pyplot as plt
import draw as draw
import plt_lib as pl

if __name__ == '__main__' :
    read_city_path = '.\\..\\data\\tsp_data.txt'
    result_file = 'result.txt'
    city = draw.read_point(read_city_path)
    # print(city)
    draw.draw_coordinate(city)
    info, result = draw.read_answer(result_file)
    print(info)
    # print(result)
    
    result_line = []
    for i in range(len(result)-1) :
        index = int(result[i][0])
        index2 = int(result[i+1][0])
        result_line.append([])
        result_line[-1].append(city[index][0])
        result_line[-1].append(city[index][1])
        result_line[-1].append(city[index2][0])
        result_line[-1].append(city[index2][1])
    
    print(result_line)
    pl.draw_2d_line(result_line)
    image_file = info[0][10:-1]
    image_file += '.png'
    plt.savefig(image_file)