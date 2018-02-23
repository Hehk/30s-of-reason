type schema('a) = {
  .
  "resolvers": {. "Query": 'a},
  "typeDefs": string
};

type config = {. "schema": GraphQL.Type.schema};

[@bs.module "apollo-link-schema"] [@bs.new]
external _make : config => ReasonApolloTypes.apolloLink = "SchemaLink";

let make = _make;
