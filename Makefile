#
# Makefile that takes care of handing in your project.
#
all:
	@echo "This is only to hand in your project. 'make handin' will submitt your latest copy."
	@echo "and 'make check' will print out the date and time of your last handin."

handin:
	rutool handin -c dast25 -p project1 *
	rutool check -c dast25 -p project1

check:
	@rutool check -c dast25 -p project1
