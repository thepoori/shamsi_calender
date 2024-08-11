#include <stdio.h>
#include <string.h>
#include <time.h>
struct date{
	int year;
	int month;
	int day;
};



const char *months[] = {"Farvardin" , "Ordibehesht" ," Khordad" ,"Tir" ,"Mordad"
	, "Shahrivar", "Mehr" , "Aban" , "Azar" , "Dey" , "Bahman" ,
	"Esfand"
};
int leap_year(int year);
void print_cal(struct date d , int is_leap , int weekday);
struct date convert(struct tm *date , int leap);


int main(){
	time_t now;
	struct tm *date;
	time(& now);
	date = localtime(&now);
	int wd = date->tm_wday;
	struct date dt = convert(date, leap_year(date ->tm_year + 1900));
	print_cal(dt , leap_year(date ->tm_year + 1900) , wd);
	return 0;

}


int leap_year(int year){
	if ((year % 4 == 0 && year % 100 !=0 ) || (year % 400 ==0 ))
	return 0;
		return 1;
}




struct date convert(struct tm *date, int leap) {
	struct date convert_date;
	int gregorian_day = date->tm_yday + 1;
	int persian_day_offset = (leap ? 80 : 79);
	int day_of_year = gregorian_day - persian_day_offset;

	if (day_of_year >= 0) {
		convert_date.year = date->tm_year + 1900 - 621;
	} else {
		convert_date.year = date->tm_year + 1900 - 622;
		day_of_year += 365 + leap;
	}

	if (day_of_year < 186) {
		convert_date.month = (day_of_year / 31) + 1;
		convert_date.day = (day_of_year % 31);
	} else {
		day_of_year -= 186;
		convert_date.month = (day_of_year / 30) + 7;
		convert_date.day = (day_of_year % 30) ;
	}

	return convert_date;
}


void print_cal(struct date d , int is_leap ,int weekday ){
	short m_day;
	char header[200] = "";
	

	char add_num[200] = "";
	sprintf(header , "%10s %i\n%s\n" , months[d.month -1] , d.year , "Su Mo Tu We Th Fr Sa");
	if (d.month < 6)m_day = 31;
	else if (d.month > 6 && d.month < 12) m_day = 30;
	else {
		if (is_leap)
			m_day = 29;
		else
			m_day = 28;
	}
	for (int i = 0; i <= (weekday); i++) {
		strcat(header, "  " );
	}

	strcat(header, " ");

	for(int i =1 ; i <= m_day; i++){
		if (i == d.day){
			sprintf(add_num, "\e[0;30m\e[47m%*i\e[0m" , (i < 10) ? 2 : 0 ,i);
		}else {
			sprintf(add_num, "%*i" , (i < 10) ? 2 : 0 ,i);
		}
		strcat(header , add_num);
		strcat(header, " ");
		if ( ((i +(weekday + 1)))% 7 == 0)
			strcat(header,"\n");

	}


	printf("%s\n" , header);
}
