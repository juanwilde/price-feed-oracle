#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

using eosio::name;
using eosio::asset;
using eosio::check;
using eosio::symbol;
using eosio::symbol_code;
using eosio::same_payer;
using std::string;

class [[eosio::contract]] oracle : public eosio::contract {
public:
	using contract::contract;
	ACTION push(const name& user, const string& data);
	ACTION setconfig(const uint64_t id, const uint64_t value);
	[[eosio::on_notify("everipediaiq::transfer")]] void
	ontransfer(const name& from, const name& to, const asset& quantity, const string& memo);

private:
	struct [[eosio::table]] balances_t {
		asset balance;
		uint64_t primary_key() const {
			return 0;
		}
	};

	struct [[eosio::table]] config_t {
		uint64_t id;
		uint64_t value;

		uint64_t primary_key() const {
			return id;
		}
	};

	// TODO: oracle tables

	typedef eosio::multi_index<name("balances"), balances_t> balancetbl;
	typedef eosio::multi_index<name("config"), config_t> configtbl;

	static constexpr name IQ_CONTRACT = "everipediaiq"_n;
	static constexpr symbol IQ_SYMBOL = symbol(symbol_code("IQ"), 3);
};
