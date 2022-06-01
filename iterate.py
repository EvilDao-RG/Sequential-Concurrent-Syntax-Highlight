import os
contenido = os.listdir('textFiles')

with open('dir.txt', 'w') as file:
    for i in contenido:
        file.write(i[:-4])
        file.write('\n')