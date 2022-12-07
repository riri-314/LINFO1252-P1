philosophe:
	make -C Philosophe

prodcons:
	make -C Producteur_Consomateur

lect_ecri:
	make -C Lecteurs_écrivains

test_and_set:
	make -C Test_and_set

test_test_and_set:
	make -C Test_test_and_set

clean: 
	make clean -C Philosophe
	make clean -C Producteur_Consomateur
	make clean -C Lecteurs_écrivains
	make clean -C Test_and_set
	make clean -C Test_test_and_set

csv_philosophe:
	make philosophe
	make csv -C Philosophe

csv_prodcons:
	make prodcons
	make csv -C Producteur_Consomateur

csv_lect_ecri:
	make lect_ecri
	make csv -C Lecteurs_écrivains

csv_test_and_set:
	make test_and_set
	make csv -C Test_and_set

csv_test_test_and_set:
	make test_test_and_set
	make csv -C Test_test_and_set

plot:
	make csv_philosophe
	make csv_prodcons
	make csv_lect_ecri
	make csv_test_and_set
	make csv_test_test_and_set
	python3 plot.py

clean_pictures:
	rm -f Pictures/philo.png
	rm -f Pictures/prodcons.png
	rm -f Pictures/lect_ecri.png
	rm -f Pictures/tas_tts.png