import socket
import json


def main():
    host = '127.0.0.1'  # Localhost
    port = 8080  # Arbitrary non-privileged port

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        print(f"Server started at {host}:{port}")

        s.listen()
        conn, addr = s.accept()

        with conn:
            print('Connected by', addr)
            value = 1.1
            while True:
                try:
                    data = conn.recv(1024).decode("utf-8")
                    obj = json.loads(data)

                    print(f"Got: msg={obj['msg']}, value={obj['value']}")

                    send = {
                        "value": value
                    }

                    conn.send(json.dumps(send).encode("utf-8"))

                    value = value + 0.1

                except Exception as e:
                    break


if __name__ == "__main__":
    main()
