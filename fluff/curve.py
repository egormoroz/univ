from numpy.linalg import det

'''
# 807
a = [[5,4,8,-32,-56,80],[5,12,0,-22,-12,-19],[1,-4,4,4,-3,-7],[1,-5,4,1,2,-2]]
a += [[4,-12,9,-2,3,-2],[9,-4,6,16,-8,-2],[8,6,0,-26,-12,11],[1,-2,1,-10,-6,25]]
a += [[2,-5,-12,-1,26,-10],[4,-4,1,-6,3,-4],[2,4,5,-6,-8,-1],[1,-12,-4,12,8,5]]
a += [[9,24,16,-230,110,-475],[3,1,-2,-5,5,-2],[4,-12,9,-20,30,16],[5,6,5,-6,-10,-3]]
a += [[0,12,5,-12,-22,-19],[4,-4,1,-3,4,-7],[4,16,15,-8,-22,-5],[4,4,1,16,8,15]]
'''

def invs(a11, a12, a22, a1, a2, a0):
    s = a11 + a22
    d = a11*a22-a12**2
    D = det([[a11,a12,a1],[a12,a22,a2],[a1,a2,a0]])
    K = a11*a0-a1**2+a22*a0-a2**2
    return (s,d,D,K)

def own_nums(a11, a12, a22):
    b=a11+a22
    d=(b**2-4*(a11*a22-a12**2))**(1/2)
    return ((b+d)/2, (b-d)/2)

def info(a):
	eps = 1e-5
	r = list(invs(a[0], a[1]/2, a[2], a[3]/2,a[4]/2,a[5]))
	r.extend(list(own_nums(a[0], a[1]/2,a[2])))
	print('\n'.join(list(map(lambda x: x[0]+str(x[1]), zip(['S = ', 'd = ', 'D = ', 'K = ', 'l_1 = ', 'l_2 = '], r)))))
	if r[1] > eps:
		if r[0]*r[2] < -eps:
			print('ellipse')
		elif r[0]*r[2] > eps:
			print('imaginary ellipse')
		else:
			print('a pair of imaginary intersecting lines')
	elif r[1] < -eps:
		if abs(r[2]) > eps:
			print('hyperbole')
		else:
			print('a pair of intersecting lines')
	elif abs(r[2]) > eps:
		print('parabola')
	elif r[3] < -eps:
		print('a pair of parallel lines')
	elif r[3] > eps:
		print('a pair of imaginary parallel lines')
	else:
		print('a pair of overlapping lines')