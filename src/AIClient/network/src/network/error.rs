use colored::Colorize;
use std::fmt::Display;

#[derive(Debug)]
pub enum NetworkError {
    SocketOpenFailed(String),
    ConnectFailed(String),
    ConnectionLimitReached,
    WriteError(std::io::Error),
    ReadError(std::io::Error),
    AcceptError(AcceptorError),
}

#[derive(Debug)]
pub enum AcceptorError {
    SocketOpenFailed,
    BadFileDescriptor,
    BadAddress,
    InvalidState,
    ResourceExhausted,
    PermissionDenied,
    ProtocolError,
    UnknownError,
    BindFailed,
    ListenFailed,
}

impl std::error::Error for NetworkError {
    fn source(&self) -> Option<&(dyn std::error::Error + 'static)> {
        match self {
            NetworkError::ConnectionLimitReached => None,
            NetworkError::WriteError(e) | NetworkError::ReadError(e) => Some(e),
            NetworkError::AcceptError(e) => Some(e),
            _ => None,
        }
    }
}

impl Display for NetworkError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            NetworkError::ConnectionLimitReached => {
                write!(f, "{}Connection limit reached!", "[NETWORK] ".red())
            }
            NetworkError::WriteError(err) => {
                write!(f, "{}Write error: {err}", "[NETWORK] ".red())
            }
            NetworkError::ReadError(err) => {
                write!(f, "{}Read error: {err}", "[NETWORK] ".red())
            }
            NetworkError::AcceptError(err) => {
                write!(f, "{}{err}", "[NETWORK] ".red())
            },
            NetworkError::SocketOpenFailed(err) => {
                write!(f, "{}Failed to open socket for {err}", "[NETWORK] ".red())
            },
            NetworkError::ConnectFailed(err) => {
                write!(f, "{}Failed to connect to peer in {err}", "[NETWORK] ".red())
            },
        }
    }
}

impl std::error::Error for AcceptorError {}

impl Display for AcceptorError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            AcceptorError::BadFileDescriptor => {
                write!(
                    f,
                    "{}Bad file descriptor, socket operation on non-socket.",
                    "[ACCEPTOR] ".red()
                )
            }
            AcceptorError::BadAddress => {
                write!(f, "{}Bad address.", "[ACCEPTOR] ".red())
            }
            AcceptorError::InvalidState => {
                write!(f, "{}Invalid state.", "[ACCEPTOR] ".red())
            }
            AcceptorError::ResourceExhausted => {
                write!(f, "{}Resource exhausted.", "[ACCEPTOR] ".red())
            }
            AcceptorError::PermissionDenied => {
                write!(f, "{}Permission denied.", "[ACCEPTOR] ".red())
            }
            AcceptorError::ProtocolError => {
                write!(f, "{}Protocol error.", "[ACCEPTOR] ".red())
            }
            AcceptorError::UnknownError => {
                write!(f, "{}Unknown error.", "[ACCEPTOR] ".red())
            },
            AcceptorError::SocketOpenFailed => {
                write!(f, "{}Failed to open socket.", "[ACCEPTOR] ".red())
            },
            AcceptorError::BindFailed => {
                write!(f, "{}Failed to bind socket to address.", "[ACCEPTOR] ".red())
            },
            AcceptorError::ListenFailed => {
                write!(f, "{}Failed to listen on opened port.", "[ACCEPTOR] ".red())
            },
        }
    }
}
