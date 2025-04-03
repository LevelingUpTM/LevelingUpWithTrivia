import socket

HOST = 'localhost'  # Server address
PORT = 5555         # Port number that the server is listening on

def run_client():
    # Create a socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server 
        client_socket.connect((HOST, PORT))
        print("Connected to the server!")

        # Receive "hello" from the server
        message = client_socket.recv(1024).decode()  # Receive the message
        print("Received from server:", message)

        # After receiving "hello", send "hi" to the server
        if message == "hello":
            client_socket.sendall(b"hi")

        # Receive server's response
        response = client_socket.recv(1024)
        print("Server response:", response.decode())

    finally:
        # Close the connection
        client_socket.close()
        print("Connection closed.")


if __name__ == "__main__":
    run_client()
