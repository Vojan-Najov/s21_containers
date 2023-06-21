format:
	cp materials/linters/.clang-format .
	clang-format -i include/*.h
	rm .clang-format

.PHONE: format
