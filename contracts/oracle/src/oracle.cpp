#include <oracle/oracle.hpp>

void oracle::push(const name& user, const string& data) {
	require_auth(user);

	// TODO: validate & store
}
void oracle::ontransfer(const name& from, const name& to, const asset& quantity, const string& memo) {
	if (from == _self) {
		return;
	}
	check(to == _self, "contract is not involved in this transfer");
	check(quantity.symbol == IQ_SYMBOL, "only bounties in IQ");

	balancetbl balances(_self, 0);
	auto balance = balances.find(0);
	if (balance == balances.end()) {
		balances.emplace(_self, [&](auto& t) { t.balance = quantity; });
	} else {
		balances.modify(balance, same_payer, [&](auto& t) { t.balance += quantity; });
	}
}
void oracle::setconfig(const uint64_t id, const uint64_t value) {
	require_auth(_self);

	configtbl config(_self, _self.value);

	auto conf = config.find(id);
	if (conf == config.end()) {
		config.emplace(_self, [&](auto& c) {
			c.id = id;
			c.value = value;
		});
	} else {
		config.modify(conf, same_payer, [&value](auto& c) { c.value = value; });
	}
}
