import pdb

def transform():
	for i in range (1,2):
			with open("./t"+str('%04d' % i)+".txt", "w+") as myfile:
					with open('./t'+str('%04d' % i)+'.dat') as fin:
							next(fin)
							myfile.write('ID, mass, x, y, z\n')
							rows = (line.split() for line in fin)
							for row in rows:
								if len(row) == 0: 
									continue
								line = ', '.join(row)
								myfile.write(''.join([line,"\n"]))

def inv_transform():
	i = 1
	with open("./t"+str('%04d' % i)+".txt", "r") as myfile:
			with open('./t'+str('%04d' % i)+'.dat', 'w') as fin:
					fin.write(".DAT file, you may want to remove this line")
					#myfile.write('ID, mass, x, y, z\n')
					rows = (line.split(',') for line in myfile)
					for row in rows:
							line = ' '.join(row)
							fin.write(''.join([line,"\n"]))

transform()