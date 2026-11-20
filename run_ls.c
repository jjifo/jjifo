#include "main.h"

void run_ls() {
    WINDOW *sub_win;
    int highlight = 1; //현재 커서서의 위치 메뉴 번호 1:-l, 2:-a, 3:-h, 4:Enter - Run
    int c; // 사용자 키보드 입력 값 저장 변수
    // 옵션의 체크 상태
    // 1: 체크됨, 0: 비어있음, -l과 -h는 기본 체크되어 있음
    int opt_l = 1;
    int opt_a = 0;
    int opt_h = 1;

    // TUI 창 설정 코드
    sub_win = newwin(30, 100, 3, 25);
    keypad(sub_win, TRUE);

    while(1) {
        box(sub_win, 0, 0);
        mvwprintw(sub_win, 0, 4, " ls - File List Options ");
        
        mvwprintw(sub_win, 2, 3, "Toggle Options (Press Space to select):");
        
        // Option 1: -l
        // highligt가 1이면 글자와 배경색 반전 : 글 적는게 보이게 강조 표시
        if(highlight == 1) wattron(sub_win, A_REVERSE);
        mvwprintw(sub_win, 4, 5, "[%s] -l Detailed View", opt_l ? "X" : " ");
        // opt_l이 참(1)이면 X, 거짓(0)이면 공백을 출력
        if(highlight == 1) wattroff(sub_win, A_REVERSE);

        // Option 2: -a
        if(highlight == 2) wattron(sub_win, A_REVERSE);
        mvwprintw(sub_win, 5, 5, "[%s] -a Show hidden files", opt_a ? "X" : " ");
        if(highlight == 2) wattroff(sub_win, A_REVERSE);

        // Option 3: -h
        if(highlight == 3) wattron(sub_win, A_REVERSE);
        mvwprintw(sub_win, 6, 5, "[%s] -h Human-readable file sizes", opt_h ? "X" : " ");
        if(highlight == 3) wattroff(sub_win, A_REVERSE);

        // Execute Button
        if(highlight == 4) wattron(sub_win, A_REVERSE);
        mvwprintw(sub_win, 9, 15, " Enter — Run ");
        if(highlight == 4) wattroff(sub_win, A_REVERSE);

        mvwprintw(sub_win, 11, 3, "↑↓ Move | Space Toggle | Esc Go Back");
        // 지금까지의 내용 실제 터미널 화면에 출력
        wrefresh(sub_win);

        c = wgetch(sub_win);
        // 사용자가 키 입력시까지 대기, 입력내용을 c에 저장
        switch(c) {
            // 위아래 화살표로 커서 움직이는 기능
            case KEY_UP:
                if(highlight > 1) highlight--;
                break;
            case KEY_DOWN:
                if(highlight < 4) highlight++;
                break;
            case ' ': // 스페이스바 누르면 조건을 반전
                if(highlight == 1) opt_l = !opt_l;
                else if(highlight == 2) opt_a = !opt_a;
                else if(highlight == 3) opt_h = !opt_h;
                break;
            case 10: //enter키 눌렀을 때의 줄바꿈 코드
                if(highlight == 4) {
                    char cmd[100] = "ls";
                    if(opt_l || opt_a || opt_h) {
                        strcat(cmd, " -"); //cmd 뒤에 - 붙임
                        if(opt_l) strcat(cmd, "l"); // ls - l
                        if(opt_a) strcat(cmd, "a"); // ls - a
                        if(opt_h) strcat(cmd, "h"); // ls - h
                    }
                    strcat(cmd, " .");

                    // Ncurses ကို ခေတ္တရပ်ပြီး Terminal ပုံစံဖြင့် Command Run ပြခြင်း
                    endwin();
                    printf("\n[실행할 명령어]: %s\n", cmd);
                    printf("----------------------------------------\n");
                    system(cmd); // 문자열을 실제 리눅스 셀 명령어처럼 실행
                    printf("----------------------------------------\n\n");
                    printf("계속하려면 아무 키나 누르세요...");
                    getchar();
                    
                    // Ncurses သို့ ပြန်ဝင်ရန်
                    refresh();
                }
                break;
            case 27: // Esc နှိပ်လျှင် Main Menu သို့ ပြန်သွားရန်
                delwin(sub_win);
                return;
        }
    }
}