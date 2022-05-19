from matplotlib import pyplot as plt
import draw as draw
import plt_lib as pl

if __name__ == '__main__' :
    read_city_path = '.\\..\\data\\tsp_data.txt'
    city = draw.read_point(read_city_path)
    # print(city)
    draw.draw_coordinate(city)
    result = draw.read_answer('')
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
    plt.savefig('result_image.png')