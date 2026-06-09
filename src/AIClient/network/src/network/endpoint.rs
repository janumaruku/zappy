use libc::in_addr_t;
use std::net::Ipv4Addr;

pub struct Endpoint {
    port: u16,
    hostname: String,
    address: libc::sockaddr_in,
}

impl Endpoint {
    pub fn new(port: u16, host: &str) -> Self {
        Endpoint {
            port,
            hostname: host.to_string(),
            address: libc::sockaddr_in {
                sin_family: libc::AF_INET as libc::sa_family_t,
                sin_port: libc::htons(port),
                sin_addr: libc::in_addr {
                    s_addr: match host.is_empty() {
                        true => libc::INADDR_ANY as in_addr_t,
                        false => u32::from(host.parse::<Ipv4Addr>().unwrap()).to_be(),
                    },
                },
                sin_zero: [0; 8],
            },
        }
    }

    pub fn from_sockaddr(address: libc::sockaddr_in) -> Self {
        Endpoint {
            port: libc::ntohs(address.sin_port),
            hostname: Ipv4Addr::from(u32::from_be(address.sin_addr.s_addr)).to_string(),
            address,
        }
    }

    pub fn port(&self) -> u16 {
        self.port
    }

    pub fn host(&self) -> &str {
        &self.hostname
    }

    pub fn address(&self) -> libc::sockaddr_in {
        self.address
    }
}
