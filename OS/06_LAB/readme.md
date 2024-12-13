# Task:

You are tasked with creating a simple chat system between
two users on the same machine, communicating via named pipes.
---
Implement two programs, chat_sender and chat_receiver,
where:
- chat_sender allows a user to type messages and sends them via a named pipe. It also reads messages from chat_receiver.
- chat_receiver displays incoming messages from the named pipe. It also sends messages to chat_sender.
- The programs should run on separate terminals, with bi-directional communication. Use two named pipes for full-duplex communication.
- It should be in an infinite loop/or you can add an exit condition such as ends on abort or exit.