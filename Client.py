import socket
import json
import struct

HOST = 'localhost'  # Server address
PORT = 5555         # Port number that the server is listening on


class UserClient:
    """
    A TCP client that communicates with the cpp server.
    Protocol format:
    - 1 byte for request code (unsigned char)
    - 4 bytes for payload length (unsigned int)
    - JSON - data
    """

    def __init__(self, host = HOST, port = PORT):
        """
        Initialize the client with host and port.
        """
        self.host = host
        self.port = port
        self.sock = socket.socket()

    def connect(self):
        """
        Connect to the server.
        :return: True if connection is successful, False otherwise.
        """
        try:
            self.sock.connect((self.host, self.port))
            print(f"Connected to {self.host}:{self.port}")
            return True
        except Exception as e:
            print("Connection error:", e)
            return False
        


    def send(self, code, data):
        """
        Send a request to the server.

        :param code: Request code (1 = login, 2 = signup)
        :param data: Dictionary to send as JSON
        :return: Response from server or None on error
        """
        try:
            # Convert dictionary to JSON and encode to bytes
            payload = json.dumps(data).encode()

            # Pack header: 1-byte code + 4-byte payload length (it turns the values into binary data)
            header = struct.pack('>BI', code, len(payload))

            # Send header and payload
            self.sock.sendall(header + payload)

            # Receive and return the server's response
            return self.receive()
        except Exception as e:
            print("Send error:", e)

    def receive(self):
        """
        Receive and decode a response from the server.
        :return: Decoded JSON response or None on error
        """
        try:
            # Read the 5-byte header
            header = self.sock.recv(5)
            if len(header) < 5:
                raise Exception("Incomplete header")

            # Unpack header into response code and payload length
            code, length = struct.unpack('>BI', header)

            # Read the JSON payload based on length
            payload = self.sock.recv(length)
            while len(payload) < length:
                payload += self.sock.recv(length - len(payload))

            # Decode and return the JSON data
            return json.loads(payload.decode())
        
        except Exception as e:
            print("Receive error:", e)

    def close(self):
        """
        Close the connection to the server.
        """
        self.sock.close()
        print("Disconnected")


# Example usage
if __name__ == "__main__":
    client = UserClient()

    if client.connect():

        # Send login request (code 1)
        login = {
            "username": "test", 
            "password": "1234"
        }
        
        print("Login: ", client.send(1, login))

        # Send signup request (code 2)
        signup = {
            "username": "new",
            "password": "abcd", 
            "email": "new@example.com"
        }
        print("Signup: ", client.send(2, signup))

        client.close()
