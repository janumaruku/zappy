use colored::Colorize;
use std::fmt::Display;

#[derive(Debug)]
pub enum NetworkError {
    ConnectionLimitReached,
    WriteError(std::io::Error),
    ReadError(std::io::Error),
    AcceptError(AcceptorError),
}

#[derive(Debug)]
pub enum AcceptorError {
    BadFileDescriptor,
    BadAddress,
    InvalidState,
    ResourceExhausted,
    PermissionDenied,
    ProtocolError,
    UnknownError,
}

impl std::error::Error for NetworkError {
    fn source(&self) -> Option<&(dyn std::error::Error + 'static)> {
        match self {
            NetworkError::ConnectionLimitReached => None,
            NetworkError::WriteError(e) | NetworkError::ReadError(e) => Some(e),
            NetworkError::AcceptError(e) => Some(e),
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
            }
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
            }
        }
    }
}
