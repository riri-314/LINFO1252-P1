philosophe:
	make -C Philosophe

prodcons:
	make -C Producteur_Consomateur

test_and_set:
	make -C Test_and_set

test_test_and_set:
	make -C Test_test_and_set

clean: 
	make clean -C Philosophe
	make clean -C Producteur_Consomateur
	make clean -C Test_and_set
	make clean -C Test_test_and_set

csv_philosophe:
	make philosophe
	make csv -C Philosophe

csv_prodcons:
	make prodcons
	make csv -C Producteur_Consomateur

csv_test_and_set:
	make test_and_set
	make csv -C Test_and_set

csv_test_test_and_set:
	make test_test_and_set
	make csv -C Test_test_and_set

plot:
	make csv_philosophe
	make csv_prodcons
	make csv_test_and_set
	make csv_test_test_and_set
	python3 plot.py
