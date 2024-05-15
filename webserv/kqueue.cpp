
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <vector>

void exit_with_perror(const string& msg)
{
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

void disconnect_client(int client_fd, map<int, string>& clients)
{
    std::cout << "client disconnected: " << client_fd << std::endl;
    close(client_fd);
    clients.erase(client_fd);
}

int main()
{
    int serv_socket;
    struct sockaddr_in serv_addr;

    if(serv_socket == socket(PF_INET, SOCK_STREAM, 0) == -1)
        printf("error\n");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    bind(serv_socket, (struct sockaddr*)&serv_addr, sizeof(sever_addr));

    listen(serv_socket, 5);

    fcntl(serv_socket, F_SETFL, O_NONBLOCK);


    int kq;

    kq == kqueue();

    map<int, string> clients;
    vector<struct kevent> change_list;
    // 관찰할 fd, process id를 입력해준다.
    struct kevent event_list[8];

/**

   key -> struct kevent 인스턴스를 가르키는 포인터
   ident -> 이 이벤트에 대한 식별자 (파일 디스크립터, 프로세스 아이디)
   filter -> monitoring 되는 이벤트의 유형 -> EVFILT_READ, EVFILT_WRITE read, write event
   flags -> event를 kqueue에 추가, 수정, 제거하는 방법을 제어하는 플래그
   EV_ADD, EV_ENABLE, EV_DISABLE, EV_DELETE

*/
     
    // 관찰할 FD를 추가하고 read event가 발생했을때를 확인하겠다는의미
    std::cout << "echo server start!\n";

    int new_events;
    struct kevent* curr_event;

    while (1)
    {
        new_events = kevent(kq, &change_list[0], change_list.size(), event_list, 8, NULL);
        /**
            kevent()는 인자 kq로 전달된 kqueue에 새로 모니터링할 이벤트를 등록하고, 발생하여 아직 처리도지 않은
            이벤트의 갯수를 return 해준다.
            kq  -> kqueue
            changelist -> kqueue에 등록, 수정, 제거할 이벤트를 포함한다.
            changelist_size() -> 변경 수 이  인자는 changlist 배열에 포함된 이벤트의 갯수를 나타낸다.
            -> nchanges 갯수만큼 이벤트를 처리한다.
            -> nchanges 값이 0이면 kevent() 함수는 이벤트를 등록, 수정 또는 제거하지 않고 대기만 합니다.
            event_list 
            -> 이 포인터는 struct kevent 구조체 배열을 가르킨다.
            이 배열은 kevent()함수가 반환하는 발생한 이벤트를 포함한다. 마찬가지로 kevent struct이다.
            kevent 함수에 의해 반환할 이벤트들을 저장하는데 사용된다.
            8 event_list 배열에서 kevent 함수가 반환할 수 있는 최대 이벤트 수를 지정한다.
            이는 함수가 이번 호출에서 처리할수있는 이벤트의 최대갯수를 의미한다. event_list 배열의 크기와 
            동일해야한다.
            이 매개변수는 한번의 함수 호출로 처리할 수 있는 이벤트의 수를 제한한다.
            이 값이 너무 작으면 일부 이벤트가 누락될 수 있고, 너무크면 불필요한 메모리를 사용할 수 있다.
            따라서 이값은 서버의 부하, 이벤트 발생 빈도 및 예상 트래픽양을 고려하여 조정해야한다.

            NULL => 이 매개변수는 kevent 함수의 대기시간을 관리하는 timespec 구조체에 대한 포인터이다.
            NULL 값은 kevent function이 이벤트가 발생할때까지 무한히 대기하거나, 이미 준비된 이벤트가
            즉시 처리 될수 있음을 의미한다.
            시간을 지정하면 해당 시간이 되면 반환하게 된다.

        */
        if(new_events == -1)
            exit_with_error("kevent() error\n" + string(strerror(errno)));

        change_list.clear();
        // kevent() function 호출 후, change_list는 이전에 추가된 모든 이벤트 변경사항 포함
        // clear를 해주고 새로운 이벤트가 입력될 수 있도록 한다.

        // new_event는 대기중이던 이벤트들 중 실제로 발생한 이벤트의 수를 의미한다.
        // 발생한 event를 처리해준다.
        for(int i = 0; i < new_events; ++i)
        {
            // 발생한 이벤트 리스트에서 현재 리스트를 가져옴
            curr_event = &event_list[i];

            if(curr_event->flags & EV_ERROR) // 발생한 이벤트가 오류가 있는지 확인
            {
                if(curr_event->ident == server_socket) // 오류가 서버오류인지
                    exit_with_perror("server socket error!\n");
                else{ //클라이언트 오류인지 확인해주고
                    std::cerr << "client socket error" << sgtd::endl;
                    // 클라이언트 연결해제
                    disconnect_client(curr_event->ident, clients);
                }
            }
            // 발생한 이벤트가 읽기 이벤트인지 확인
            else if(curr_event->filter == EVFILT_READ)
            {
                // 서버에서 받은 이벤트라면
                if(curr_event->ident == server_socket)
                {
                    int client_socket;
                    // 클라이언트 수락해주기
                    if((client_socket = accept(server_socket, NULL, NULL)) == -1)
                        exit_with_perror("accept() error!\n" + string(strerror(errno)));
                    std::cout << "accept new client :" << client_socket << std::endl;
                    // 클라이언트 소켓을 non_block으로 처리해주기
                    fcntl(client_socket, F_SETFL, O_NONBLOCK);
                    // add event 클라이언트 이벤트
                    // 클라이언트도 이벤트 목록에 추가해주기
                    change_events(change_list, client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
                    // 읽기 이벤트추가
                    change_events(change_list, client_socket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
                    // 쓰기 이벤트추가
                    clients[client_socket] = "";
                }
                else if(clients.find(curr_event->ident) != clients.end())
                // 클라이언트 이벤트에서 발생한 오류인지 확인
                {
                    char buf[1024];
                    // 클라이언트에서 데이터 읽기
                    int n = read(curr_event->ident, buf, sizeof(buf));

                    if( n <= 0)
                    {
                        if(n < 0)
                            std::cerr <<"client read error!\n";
                        disconnect_client(curr_event->ident, clients);
                    }
                    else
                    {
                        buf[n] = '\0';
                        clients[curr_event->ident] += buf;
                        std::cout << "received data from" << curr_event->ident << ": " << clients[curr_event->ident] << std::endl;
                    }
                }
                else if(curr_event->filter == EVFILT_WRITE) // 쓰기 이벤트인지확인
                {
                    map<int, string>::iterator it = clients.find(curr_event->ident);
                    if(it != clients.end()) // 클라이언트 소켓이 존재하는지 확인
                    {
                        if(clients[curr_event->ident] !="") // 클라이언트에게 보낼 데이터가 있는지 확인하기
                        int n;
                        if((n = write(curr_event->ident, clients[curr_event->ident].c_str(), clients[curr_event->ident].size()) == -1))
                        {
                            std::cerr << "client write error!\n"; // 쓰기 오류메세지 출력
                            disconnect_client(curr_event->ident, clients);
                        }
                        else
                            clients[curr_event->ident].clear(); 
                        // 데이터 전송 후 클라이언트 데이터 버퍼 비움.
                    }
                }
            }
        }
    }
}