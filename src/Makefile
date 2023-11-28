CC=gcc
CFLAGS=-c
LDFLAGS=-lcheck -lm -lsubunit
TESTSRC=test_cases/test.c
LIBSRC=$(filter-out $(TESTSRC), $(wildcard *.c))
TESTOBJ=$(TESTSRC:.c=.o)
LIBOBJ=$(LIBSRC:.c=.o)
EXECUTABLE=result_file
STATICLIB=s21_decimal.a
LINTDIR=../materials/linters
LCOVEXEC=$(EXECUTABLE).info
REPORTDIR=report
LEAKS_REPORT_FILE=leaks_report.txt
LEAKS_LINUX = valgrind --leak-check=full -v --log-file=$(REPORTDIR)/$(LEAKS_REPORT_FILE)
LEAKS_MAC = CK_FORK=no leaks -atExit --
UNAME_S = $(shell uname -s)

.PHONY: all build clean lint test gcov_report

all: build

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

$(STATICLIB): $(LIBOBJ)
	ar rcs $@ $^

build: clean $(TESTOBJ) $(STATICLIB)
	$(CC) $(TESTOBJ) $(STATICLIB) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -rf *.o $(EXECUTABLE) $(STATICLIB) *.gcno *.gcda *.gcov $(LCOVEXEC) $(REPORTDIR) ./test_cases/*.o \
	./test_cases/*.gcno ./test_cases/*.gcda ./test_cases/*.gcov

test: build
	./$(EXECUTABLE)

lint:
	@cp $(LINTDIR)/CPPLINT.cfg . && \
	python3 $(LINTDIR)/cpplint.py --extensions=h *.h; \
	python3 $(LINTDIR)/cpplint.py --extensions=c *.c
	@rm -f CPPLINT.cfg

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem s21*.c s21*.h

leaks: build
	mkdir $(REPORTDIR)
ifeq ($(UNAME_S), Linux)
	$(LEAKS_LINUX) ./$(EXECUTABLE)
endif
ifeq ($(UNAME_S), Darwin)
	$(LEAKS_MAC) ./$(EXECUTABLE)
endif

gcov_report: CFLAGS+=--coverage
gcov_report: LDFLAGS+=--coverage
gcov_report: test
	lcov -t $(EXECUTABLE) -o $(LCOVEXEC) -c -d .
	genhtml -o $(REPORTDIR) $(LCOVEXEC)
