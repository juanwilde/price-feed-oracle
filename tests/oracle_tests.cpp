#include "contracts.hpp"
#include "oracle_test_api.hpp"
#include "token_test_api.hpp"
#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

#define SUCCESS(call) BOOST_REQUIRE_EQUAL(success(), call)
#define ERROR(msg, call) BOOST_REQUIRE_EQUAL(wasm_assert_msg(msg), call)

class oracle_tester : public tester {
protected:
	oracle_test_api api;
	token_test_api iq;

public:
	oracle_tester()
		: api(N(oracle), this)
		, iq(N(everipediaiq), this) {
		create_accounts({N(alice), N(bob), N(cesar)});
		produce_blocks(2);
		init_token(N(alice));
	}

private:
	void init_token(const name& to) {
		SUCCESS(iq.push_action(
			iq.contract, iq.contract, N(create), mvo()("issuer", iq.contract)("maximum_supply", asset::from_string("1000000000.000 IQ"))));

		SUCCESS(iq.push_action(
			iq.contract, iq.contract, N(issue), mvo()("to", iq.contract)("quantity", asset::from_string("1000000000.000 IQ"))("memo", "")));

		SUCCESS(iq.transfer(iq.contract, N(alice), asset::from_string("100.000 IQ")));
		SUCCESS(iq.transfer(iq.contract, N(bob), asset::from_string("100.000 IQ")));
		SUCCESS(iq.transfer(iq.contract, N(cesar), asset::from_string("500.000 IQ")));
	}
};

BOOST_AUTO_TEST_SUITE(oracle_tests)

BOOST_FIXTURE_TEST_CASE(hello, oracle_tester) try { SUCCESS(api.push(N(cesar), "hola")); }
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
