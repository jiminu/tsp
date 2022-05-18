from matplotlib import pyplot as plt
import draw as draw

if __name__ == '__main__' :
    read_city_path = '.\\data\\tsp_data.txt'
    city = draw.read_point(read_city_path)
    draw.draw_coordinate(city)
    plt.show()