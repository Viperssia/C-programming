GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m

all:
	@echo "$(YELLOW)Компиляция...$(NC)"
	@gcc test_calculator_cmocka.c calculator.c -lcmocka -lm -o test_cmocka
	@echo "$(GREEN)Запуск тестов:$(NC)\n"
	@./test_cmocka

clean:
	rm -f test_cmocka
	@echo "$(GREEN)Очищено$(NC)"